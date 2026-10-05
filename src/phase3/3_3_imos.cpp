/**
 * Phase 3.3: いもす法 (imos法)
 * 
 * 【問題】
 * 会場に N 人の客が訪れる。客 i は半開区間 [S_i, T_i) の間滞在する。
 * 1. 同時に滞在していた客の「最大人数」を出力せよ。
 * 2. 最大人数を最初に記録した「最小の時刻」を出力せよ。
 * - 1次元いもす法により O(N + max T) で計算する。
 * 
 * 【制約】
 * - 1 <= N <= 2 * 10^5
 * - 0 <= S_i < T_i <= 2 * 10^5
 * 
 * 【入力例 1】
 * 4
 * 1 5
 * 2 6
 * 4 8
 * 3 4
 * 
 * 【出力例 1】
 * 3
 * 3
 * 
 * 【入力例 2】
 * 3
 * 0 10
 * 0 10
 * 0 10
 * 
 * 【出力例 2】
 * 3
 * 0
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<int> S(N), T(N);
  for (int i = 0; i < N; ++i) {
    cin >> S[i] >> T[i];
  }

  constexpr int T_MAX = 200000 + 5;
  vector<int> x(T_MAX, 0);

  for (int i = 0; i < N; ++i) {
    x[S[i]]++;
    x[T[i]]--;
  }

  for (int i = 1; i < T_MAX; ++i) {
    x[i] += x[i - 1];
  }

  int max_val = 0;
  int max_idx = 0;
  for (int i = 0; i < T_MAX; ++i) {
    if (max_val < x[i]) {
      max_val = x[i];
      max_idx = i;
    }
  }

  cout << max_val << '\n';
  cout << max_idx << '\n';

  return 0;
}