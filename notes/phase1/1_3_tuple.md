# 1.3 ペア・タプル・構造化束縛

## 1. 辞書順比較（Lexicographical Comparison）のルール

`std::pair` や `std::tuple` は、比較演算子（`<` や `==`）が標準で定義されており、**辞書（英和辞典）と全く同じ順序** で比較される。

### 比較の流れ
1. まず **第 1 要素** を比較する。
2. 第 1 要素が等しい場合のみ、**第 2 要素** を比較する。
3. それも等しい場合、**第 3 要素**（`tuple` の場合）を比較する……

### 競プロでの利点
自作の比較関数やラムダ式を書かなくても、`std::sort(vec.begin(), vec.end())` を呼ぶだけで、自動的に **「$X$ 昇順 $\to$ $Y$ 昇順 $\to$ 名前昇順」** の多段ソートが完了する。

---

## 2. 波括弧 `{}` による初期化（Uniform Initialization）

C++11 以降、冗長な `make_pair(a, b)` や `make_tuple(a, b, c)` を書く必要はなく、波括弧 `{}` で囲むだけで型推論されて直接構築される。

```cpp
// モダンな書き方
vector<tuple<int, int, string>> vec;
vec.push_back({x, y, s}); // 型を再記述せず直接渡せる
```

---

## 3. 構造化束縛（Structured Binding: C++17〜）

`pair` や `tuple` の中身を、1 行で意味のある変数名としてアンパック展開できる構文。

### 3つのバリエーションと使い分け

| 構文 | 動作 | コピーコスト | 用途 |
| :--- | :--- | :---: | :--- |
| `auto [x, y, s] : vec` | 各要素を **値コピー** | 大 | 内部で変更しても元の `vec` に影響させたくない場合 |
| `auto& [x, y, s] : vec` | 各要素への **非const参照** | **ゼロ** | **元の `vec` の中身を書き換えたい場合** |
| `const auto& [x, y, s] : vec` | 各要素への **const参照** | **ゼロ** | **読み取り専用（出力・判定など）の鉄板** |

### コピーコスト TLE の恐怖
`s` が長さ $10^6$ の `std::string` や `std::vector` など重いオブジェクトの場合、値コピー（`auto [x, y, s]`）を使うと **ループのたびにヒープメモリのディープコピーが発生** する。
$N = 10^5$ のループで回すと合計 $10^{11}$ 回以上のメモリアクセスとなり、**確実に TLE / MLE** を引き起こす。
**「コンテナをループで回す際は原則 `const auto&`（書き換えるなら `auto&`）」** を徹底する。

---

## 4. 実戦的最適化: `vec.reserve(N)`

`std::vector` は末尾追加（`push_back`）時に内部容量（capacity）が足りなくなると、メモリの再確保と全要素のコピー（reallocation）を行う。
あらかじめ要素数 $N$ が分かっている場合は、入力ループの前に `vec.reserve(N);` を呼ぶことで、再確保オーバーヘッドを完全に排除できる。

---

## 5. 実践コード

```cpp
/**
 * Phase 1.3: ペア・タプル・構造化束縛
 * 
 * 【問題】
 * 2次元平面上の N 個の点 (X, Y) と名前 S が与えられる。
 * 1. (X 昇順 -> Y 昇順 -> S 辞書順) でソートする。
 * 2. 参照の構造化束縛 (auto&) を用いて、全要素の Y 座標を 2 倍に更新する。
 * 3. const 参照の構造化束縛 (const auto&) を用いて、全要素を出力する。
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<tuple<int, int, string>> vec;
  vec.reserve(N);
  int X, Y;
  string S;
  for (int i = 0; i < N; i++) {
    cin >> X >> Y >> S;
    vec.push_back({X, Y, S});
  }

  // 1. 辞書順多段ソート
  sort(vec.begin(), vec.end());

  // 2. 参照束縛によるインプレース書き換え
  for (auto &[x, y, s] : vec) {
    y *= 2;
  }

  // 3. const 参照束縛による安全な出力
  for (const auto &[x, y, s] : vec) {
    cout << x << " " << y << " " << s << '\n';
  }

  return 0;
}
```
