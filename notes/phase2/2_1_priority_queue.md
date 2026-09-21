# 2.1 std::priority_queue の実践

## 1. 概要と計算量

`std::priority_queue`（優先度付きキュー）は、要素を追加しながら **「常に最大（または最小）の要素を $O(1)$ で取り出せる」** データ構造である。

| 操作 | 構文例 | 計算量 | 動作説明 |
| :--- | :--- | :---: | :--- |
| **最大/最小要素の参照** | `pq.top()` | **$O(1)$** | 木の頂点（根）を見るだけ |
| **要素の追加** | `pq.push(x)` | **$O(\log N)$** | 末尾に追加し、親と比較して登る（アップヒープ） |
| **最大/最小要素の削除** | `pq.pop()` | **$O(\log N)$** | 根を削除し、末尾要素を根に置いて降りる（ダウンヒープ） |
| **空判定** | `pq.empty()` | **$O(1)$** | 要素数が 0 か判定 |
| **要素数** | `pq.size()` | **$O(1)$** | 格納されている要素数 |

### 💡 なぜ `vector` を毎回ソートするより圧倒的に速いのか？
- `vector` に追加して毎回 `sort`: 追加 1 回につき **$O(N \log N)$**
- `priority_queue`: 追加 1 回につき **$O(\log N)$**
  - 全要素を完全にソートするのではなく、**「親は子より優先度が高い」という最小限の半順序関係だけを保つ** ため、木の深さ（約 $\log_2 N$ 段）しか計算が発生しない。

---

## 2. バイナリヒープ（二分ヒープ）の内部構造

ヒープはポインタノードを使わず、**通常の 1 次元配列（`std::vector`）** の中に敷き詰められている。

```text
       [ 5 ] (idx: 0)
      /     \
    [10]    [20] (idx: 1, 2)
    /  \
  [30] [15]      (idx: 3, 4)
```

任意のインデックス $i$ に対して、親子関係は簡単な算術式で求まる：
- **親のインデックス**: `(i - 1) / 2`
- **左の子**: `2 * i + 1`
- **右の子**: `2 * i + 2`

### ① `push`（アップヒープ / Sift-Up）
1. 配列の一番後ろ（木の末尾）に新しい要素を追加する。
2. 自分の「親」と比較し、自分の方が小さければ（最小ヒープの場合）親と入れ替える（swap）。
3. 親より小さくなくなるか、根に到達するまで上に登り続ける（最大で木の高さ $\log_2 N$ 回）。

### ② `pop`（ダウンヒープ / Sift-Down）
1. 根（最小値）を取り除くと根が空席になる。
2. 完全二分木の形を壊さないため、**配列の末尾の要素を引っこ抜いて根に持ってくる**。
3. 2 つの子と比較し、**より小さい方の子と入れ替える（swap）**。
4. 子より小さくなるか、一番下の葉に到達するまで下に潜り続ける（最大で木の高さ $\log_2 N$ 回）。

---

## 3. 宣言構文とコンテナアダプタ

`priority_queue` は内部で別のコンテナを内包する **「コンテナアダプタ」** である。

```cpp
// 1. デフォルト: 最大ヒープ（大きい順に取り出す）
priority_queue<ll> max_pq;

// 2. 最小ヒープ（小さい順に取り出す）
priority_queue<ll, vector<ll>, greater<ll>> min_pq;
```

### なぜ真ん中に `vector<ll>` を挟む必要があるのか？
- テンプレートの定義が `priority_queue<T, Container = vector<T>, Compare = less<...>>` となっている。
- 第 3 引数（比較関数 `greater`）を指定したい場合、C++ の構文規則上、**第 2 引数（デフォルトコンテナ `vector<T>`）を省略できない** ため、明示的に `vector<ll>` を挟む必要がある。

---

## 4. ダイクストラ法における `pair` の並び順

最短路問題（ダイクストラ法）では、優先度付きキューに `pair<ll, int>` を入れて探索する。

```cpp
// 🌟 正しい書き方: pair<最短距離, 頂点番号>
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
```

- **理由**: Phase 1.3 で学んだ通り、`pair` は **第 1 要素から順に比較** される。
- ダイクストラ法は「現在最も距離が短い頂点」から順に確定させる貪欲法であるため、**優先度の基準となる「距離」を第 1 引数にする必要がある**（`pair<頂点, 距離>` にすると頂点番号順に取り出されてしまい破綻する）。

---

## 5. 実践コード

```cpp
/**
 * Phase 2.1: std::priority_queue の実践
 */

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int Q;
  cin >> Q;
  priority_queue<ll, vector<ll>, greater<ll>> pq;

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;

    if (type == 1) {
      ll x;
      cin >> x;
      pq.push(x);
    } else if (type == 2) {
      if (pq.empty()) {
        cout << -1 << "\n";
      } else {
        ll val = pq.top();
        pq.pop();
        cout << val << "\n";
      }
    } else {
      int K;
      cin >> K;
      ll sum = 0LL;
      for (int j = 0; j < K; j++) {
        if (pq.empty()) {
          break;
        }
        ll val = pq.top();
        sum += val;
        pq.pop();
      }
      cout << sum << "\n";
    }
  }

  return 0;
}
```
