/**
 * Phase 3.5: 動的計画法 (DP基礎: 0-1 ナップサック問題と空間最適化)
 * 
 * 【問題】
 * N 個の品物があり、各品物 i は重さ w_i と価値 v_i を持つ。
 * ナップサックの容量 W を超えないように品物を選んだときの、価値の最大合計値を出力せよ。
 * - 空間計算量を O(W) に抑えるため 1 次元配列 dp[w] を用い、ループを降順に回す。
 * 
 * 【制約】
 * - 1 <= N <= 100
 * - 1 <= W <= 10^5
 * - 1 <= w_i <= W
 * - 1 <= v_i <= 10^9
 * 
 * 【入力例 1】
 * 4 5
 * 2 3
 * 1 2
 * 3 6
 * 2 2
 * 
 * 【出力例 1】
 * 9
 * 
 * 【入力例 2】
 * 3 8
 * 3 30
 * 4 50
 * 5 60
 * 
 * 【出力例 2】
 * 90
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, W;
  cin >> N >> W;

  vector<int> w(N);
  vector<ll> v(N);
  for (int i = 0; i < N; i++) {
    cin >> w[i] >> v[i];
  }

  vector<ll> dp(W + 1, 0);
  for (int i = 0; i < N; i++) {
    // 降順にループすることで、同じアイテムを複数回使用するのを防ぐ。
    for (int j = W; j >= w[i]; j--) {
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
  }

  cout << dp[W] << '\n';

  return 0;
}