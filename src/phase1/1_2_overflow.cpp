/**
 * Phase 1.2: 整数型とオーバーフロー対策
 * 
 * 【問題】
 * 4つの整数 N, k, A, B が与えられる。
 * 1. 1 から N までの総和 N(N+1)/2 を計算して出力する。
 * 2. 2^k を計算して出力する。
 * 3. A と B の積 A * B を計算して出力する。
 * 
 * 【制約】
 * - 1 <= N <= 10^9
 * - 0 <= k <= 60
 * - 1 <= A, B <= 10^9
 * 
 * 【入力例】
 * 1000000000 40 1000000000 1000000000
 * 
 * 【出力例】
 * 500000000500000000
 * 1099511627776
 * 1000000000000000000
 */

#include <iostream>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N; // 10^9
  int k;
  cin >> k; // 40
  int A;
  cin >> A; // 10^9
  int B;
  cin >> B; // 10^9

  ll sum = 1LL * N * (N + 1) / 2;
  cout << sum << "\n";
  ll power_two = 1LL << k;
  cout << power_two << "\n";
  ll large_val = 1LL * A * B;
  cout << large_val << "\n";

  return 0;
}