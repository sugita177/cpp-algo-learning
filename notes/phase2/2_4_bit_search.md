# 2.4 ビット演算とビット全探索

## 1. ビット全探索とは？

要素数 $N$ 個の集合に対して、「各要素を 選ぶ(1) / 選ばない(0)」の全パターン（部分集合）を網羅する探索手法。
$N$ 個の要素の選び方は全体で **$2^N$ 通り** 存在する。

---

## 2. 実装の基本イディオムと罠

### ① 外側のループ構文
```cpp
for (int bit = 0; bit < (1 << N); ++bit)
```
- `1 << N` は $2^N$ を表す。
- 0 から $2^N - 1$ までの整数値が、そのまま「各桁の 0/1 のビット列」として部分集合を表現する。

⚠️ **演算子優先順位の罠**:
`1 << N - 1` と書くと、`-` の方が優先順位が高いため `1 << (N - 1)`（$= 2^{N-1}$）と解釈され、**探索範囲が半分になってしまう**。必ず `1 << N` と書くか、明示的に括弧をつける。

### ② $i$ 桁目の判定（要素 $i$ が選ばれているか？）
```cpp
// 🌟 最も安全で推奨される書き方
if ((bit >> i) & 1) {
    // i 番目の要素が選ばれている
}
```
- **別解**: `if (bit & (1 << i))`
  - ※注意: ビット積 `&` は比較演算子 `==` 等よりも優先度が低いため、必ず全体を括弧で囲むこと。

---

## 3. C++20 `<bit>` ヘッダの進化

C++20 から、高速かつ型安全なビット操作関数群が標準ライブラリとして提供された。

| 関数名 | 機能 | 計算量 |
| :--- | :--- | :---: |
| **`std::popcount(x)`** | 立っているビット（1）の個数を数える | **$O(1)$** |
| **`std::has_single_bit(x)`** | $x$ が 2 のべき乗（$1, 2, 4, 8, \dots$）か判定 | **$O(1)$** |
| **`std::countl_zero(x)`** | 最上位ビットから左側に連続する 0 の個数 | **$O(1)$** |
| **`std::bit_width(x)`** | $x$ を表現するのに必要な最小ビット数 | **$O(1)$** |

### 💡 かつての `__builtin_popcount` との違い
- 従来の GCC 拡張マクロ（`__builtin_popcount(32bit)` / `__builtin_popcountll(64bit)`）と異なり、**テンプレート関数として型推論されるため、引数が 32bit でも 64bit でも同じ関数名 `std::popcount` で安全に呼べる**。
- ※引数には `unsigned int` や `unsigned long long` などの **符号なし整数** を渡す必要がある。

---

## 4. 計算量の相場観（いつビット全探索を選ぶか？）

| $N$ の値 | $2^N$（状態数） | 全体計算量 $O(N \cdot 2^N)$ | 判定 |
| :---: | :---: | :---: | :--- |
| **$N \le 15$** | $\approx 3.2 \times 10^4$ | $\approx 5 \times 10^5$ | 瞬殺（1ms 未満） |
| **$N \le 20$** | $\approx 1.05 \times 10^6$ | $\approx 2.1 \times 10^7$ | **安全圏（0.05 秒程度）** |
| **$N \le 23 \sim 25$** | $\approx 3.3 \times 10^7$ | $\approx 8 \times 10^8$ | **ギリギリの境界線**（定数倍が軽ければ 2.0 秒で通る） |
| **$N \ge 30$** | $\approx 1.07 \times 10^9$ | $\approx 3 \times 10^{10}$ | **確実に TLE** $\to$ 半分全列挙や DP を検討 |

---

## 5. 実践コード

```cpp
/**
 * Phase 2.4: ビット演算とビット全探索
 */

#include <bit>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, K;
  ll W;
  cin >> N >> K >> W;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  // 1. 2^N 通りのビット全探索
  for (int bit = 0; bit < (1 << N); bit++) {
    // 2. C++20 popcount による個数条件枝刈り
    if (popcount((unsigned int)bit) != K)
      continue;

    // 3. 選ばれた要素の総和計算
    ll sum = 0;
    for (int i = 0; i < N; i++) {
      if ((bit >> i) & 1) {
        sum += A[i];
      }
    }

    // 4. 一致判定と早期リターン
    if (sum == W) {
      cout << "Yes" << '\n';
      return 0;
    }
  }

  cout << "No" << '\n';
  return 0;
}
```
