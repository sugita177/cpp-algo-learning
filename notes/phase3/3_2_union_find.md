# 3.2 素集合データ構造 (Union-Find)

## 1. Union-Find とは？

「要素同士を同じグループに統合する（`unite`）」と「2 つの要素が同じグループに属するか判定する（`same`）」の 2 つの操作を、**ほぼ $O(1)$ という驚異的な速度** で処理できる木構造データ構造。

---

## 2. 爆速にする「2 大最適化」

素朴な木構造では、一本道に偏った場合に根を探す操作（`root`）が $O(N)$ に劣化してしまう。これを防ぐのが以下の 2 つの工夫である。

### ① 経路圧縮（Path Compression）
根を探索する際、経由したすべてのノードの親を **直接「根」に繋ぎ直す**。
```cpp
// 1行で実現できる経路圧縮
int root(int x) {
    if (par[x] < 0) return x;
    return par[x] = root(par[x]); // 親の親へ再帰し、直接根に繋ぎ変える！
}
```
一度 `root` を呼ぶと木が一瞬で深さ 1（真っ平ら）になるため、次回から $O(1)$ で根にアクセスできる。

### ② サイズによる併合（Union by size）
2 つのグループを結合する際、**「サイズの小さい方の根」を「大きい方の根の子」にする**。
これにより、木の深さが常に $O(\log N)$ 以下に抑えられる。

### 💡 アッカーマンの逆関数 $\alpha(N)$ とならし計算量
- この 2 つを併用すると、各操作 1 回あたりの **ならし計算量は $O(\alpha(N))$** となる。
- $\alpha(N)$ はアッカーマン関数の逆関数であり、宇宙の全原子数（$\approx 10^{80}$）を代入しても **たかだか 4 以下** にしかならない。
- したがって、競技プログラミングにおいて **事実上 $O(1)$（定数時間・一瞬）** として扱える。

---

## 3. 配列 1 本で「親」と「サイズ」を管理する神テクニック

競プロの実戦では、`parent` 配列と `size` 配列を別々に持たず、**負の数** を利用して配列 1 本で管理する実装が標準的である。

| 条件 | 意味 | 格納されている値 |
| :--- | :--- | :--- |
| **`par[x] >= 0`** | ノード $x$ は子ノード | **親ノードのインデックス** |
| **`par[x] < 0`** | ノード $x$ は **根（代表元）** | **`-par[x]` がそのグループの要素数（サイズ）** |

- 初期状態: 全員を `-1`（自分自身がサイズ 1 の根）で初期化する。
- マージ時: `par[x] += par[y]; par[y] = x;` とするだけで、サイズ合算と親設定が同時に完了する。

---

## 4. ⚠️ 結合処理で絶対にやってはいけないミス

```cpp
// 💣 絶対にやってはいけないミス
par[u] = v;
```
- $u$ や $v$ がすでに子や孫だった場合、元々の親との関係が破壊され、グループ全体の結合にならない。
- 結合時は、**必ず最初に `u = root(u); v = root(v);` と両方の根（親玉）を求めてから、親玉同士を繋ぐ** 必要がある。

---

## 5. 実践コード（実戦テンプレート）

```cpp
/**
 * Phase 3.2: 素集合データ構造 (Union-Find)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct UnionFind {
  vector<int> par;

  // コンストラクタ: 全員を -1 (サイズ1の根) で初期化
  UnionFind(int n) : par(n, -1) {}

  int root(int x) {
    if (par[x] < 0) return x;
    return par[x] = root(par[x]); // 経路圧縮
  }

  bool is_same(int x, int y) {
    return root(x) == root(y);
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return false;

    // Union by size (x を大きい方にする)
    if (-par[x] < -par[y]) swap(x, y);

    par[x] += par[y]; // サイズ合算
    par[y] = x;       // y を x の子にする
    return true;
  }

  int size(int x) {
    return -par[root(x)];
  }
};

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;
  UnionFind uf(N);

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;
    if (type == 0) {
      int u, v;
      cin >> u >> v;
      uf.unite(u, v);
    } else if (type == 1) {
      int u, v;
      cin >> u >> v;
      cout << (uf.is_same(u, v) ? "Yes\n" : "No\n");
    } else {
      int u;
      cin >> u;
      cout << uf.size(u) << '\n';
    }
  }

  return 0;
}
```
