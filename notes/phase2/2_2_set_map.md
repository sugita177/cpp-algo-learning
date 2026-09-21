# 2.2 平衡二分探索木コンテナ (set, multiset, map)

## 1. 赤黒木（自己平衡二分探索木）の仕組み

C++ の `std::set`, `std::multiset`, `std::map` は、内部が **赤黒木（Red-Black Tree）** と呼ばれる平衡二分探索木で実装されている。

### なぜ赤黒木が必要なのか？（二分木の弱点克服）
通常の二分探索木は、ソート済みのデータ（`1, 2, 3, 4, 5...`）が順に入力されると、右側に一本道のリストのように偏ってしまう。この場合、木の深さが $N$ になり、探索・挿入・削除が $O(N)$ に劣化してしまう。

赤黒木は、各ノードに「赤」「黒」の色を持たせ、バランスが崩れそうになると自動で **木の回転（ローテーション）や色の塗り替え** を行う。これにより、**木の高さが常に約 $\log_2 N$ 段に保たれ、どんな偏ったデータに対しても $O(\log N)$ が保証される**。

---

## 2. メンバ関数 vs 汎用アルゴリズム（競プロ最凶の罠！）

`set` や `multiset` で二分探索を行う際、呼び出し方によって **天と地ほどの計算量差** が生じる。

```cpp
auto it1 = st.lower_bound(X);                         // ⭕ パターン A: O(log N)
auto it2 = std::lower_bound(st.begin(), st.end(), X); // ❌ パターン B: O(N) TLE!!
```

### なぜ汎用アルゴリズムは $O(N)$ になるのか？
- 汎用関数 `std::lower_bound` は「中央の要素」を見る必要がある。
- しかし `set` のイテレータは双方向イテレータ（ポインタの繋がり）であるため、**中央へワープ（`+ N/2`）できない**。
- 内部で `std::advance` を使い、**1 歩ずつポインタを $N/2$ 歩辿る** ため、二分探索を行っているのに全体で $O(N)$ のステップが必要になる。
- 一方、メンバ関数 `st.lower_bound(X)` は、赤黒木の根から直接左右に分岐して降りるため、**たった $\log_2 N$ 回の比較（$O(\log N)$）で到達** できる。

> 💡 **鉄則**:
> `set`, `multiset`, `map` では、**絶対にメンバ関数 `s.lower_bound()` / `s.find()` を呼ぶこと**！

---

## 3. `multiset` の `erase` の罠（全削除 vs 1要素削除）

重複要素を保持できる `std::multiset` では、`erase` に渡す引数によって挙動が全く異なる。

```cpp
multiset<int> ms = {3, 3, 3, 5};

// 💣 危険: 値を渡すと「すべての 3」が削除される
ms.erase(3); // ms は {5} になる！

// 🌟 定石: イテレータを渡すと「その 1 つ」だけが削除される
auto it = ms.find(3);
if (it != ms.end()) {
    ms.erase(it); // ms は {3, 3, 5} になる！
}
```

- **`ms.erase(値)`**: その値を持つ要素を **すべて削除**（$O(\text{削除個数} + \log N)$）。
- **`ms.erase(イテレータ)`**: そのイテレータが指す要素 **1 つだけを削除**（ならし $O(1)$）。

---

## 4. `map` の `[]` 演算子の副作用と C++20 `contains`

### `[]` の副作用
`map` で `mp[key]` とアクセスした際、**キーが存在しない場合は「デフォルト値（`int` なら 0）で勝手に新規要素を作成・挿入」する** という仕様がある。

```cpp
// 💣 存在チェックのつもりで書くと、空の要素が勝手に作られて map のサイズが増える
if (mp[key] == 0) { ... }
```
これにより、無駄なメモリ消費（MLE）や、意図しない `size()` の増加によるバグが起きる。

### 安全なキー存在確認
C++20 から導入された **`mp.contains(key)`** を使うのが最も直感的で安全。
```cpp
// 🌟 C++20
if (mp.contains(key)) {
    // 存在する
}
```
*(※従来は `mp.count(key) > 0` や `mp.find(key) != mp.end()` を使用)*

### 💡 便利な短縮技: `mp[key]++`
`[]` の「未登録なら 0 で新規作成」という仕様を逆手に取り、出現回数のカウントは以下のようにシンプルに書ける：
```cpp
cout << mp[S]++ << "\n"; // 現在の回数を出力した後、カウントを +1
```

---

## 5. 実践コード

```cpp
/**
 * Phase 2.2: 平衡二分探索木コンテナ (set, multiset, map)
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  multiset<int> s;
  map<string, int> mp;

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;

    if (type == 1) {
      int x;
      cin >> x;
      s.insert(x);
    } else if (type == 2) {
      int x;
      cin >> x;
      // 1要素だけ削除
      auto it = s.find(x);
      if (it != s.end()) {
        s.erase(it);
      }
    } else if (type == 3) {
      int x;
      cin >> x;
      // メンバ関数で O(log N)
      auto it = s.lower_bound(x);
      if (it != s.end()) {
        cout << *it << "\n";
      } else {
        cout << -1 << "\n";
      }
    } else {
      string S;
      cin >> S;
      // C++20 contains で安全な存在チェック
      if (mp.contains(S)) {
        cout << mp[S] << "\n";
        mp[S]++;
      } else {
        cout << 0 << "\n";
        mp[S] = 1;
      }
    }
  }

  return 0;
}
```
