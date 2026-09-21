/**
 * Phase 2.4: ビット演算とビット全探索
 * 
 * 【問題】
 * N 個の正の整数 A_1, ..., A_N と目標値 W、個数条件 K が与えられる。
 * N 個の要素から「ちょうど K 個」選んで、その総和を W にできるか判定する。
 * - 2^N 通りの部分集合をビット全探索する。
 * - C++20 の std::popcount を用いて選んだ個数が K 個か判定する。
 * - 条件を満たす選び方が存在すれば Yes、存在しなければ No を出力する。
 * 
 * 【制約】
 * - 1 <= N <= 20
 * - 1 <= K <= N
 * - 1 <= A_i <= 10^9
 * - 1 <= W <= 2 * 10^10
 * 
 * 【入力例 1】
 * 5 3 14
 * 1 3 5 6 9
 * 
 * 【出力例 1】
 * Yes
 * 
 * 【入力例 2】
 * 3 2 100
 * 10 20 30
 * 
 * 【出力例 2】
 * No
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

  for (int bit = 0; bit < (1 << N); bit++) {
    ll sum = 0;
    if (popcount((unsigned int)bit) != K)
      continue;
    for (int i = 0; i < N; i++) {
      if ((bit >> i) & 1) {
        sum += A[i];
      }
    }
    if (sum == W) {
      cout << "Yes" << '\n';
      return 0;
    }
  }

  cout << "No" << '\n';
  return 0;
}