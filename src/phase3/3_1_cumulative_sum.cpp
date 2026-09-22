/**
 * Phase 3.1: 累積和・2次元累積和
 * 
 * 【問題】
 * H 行 W 列のグリッド A (マス目の値 A_{i, j}) と Q 個のクエリが与えられる。
 * 各クエリでは長方形領域 (r_1, c_1) から (r_2, c_2) (1-indexed 閉区間) が指定される。
 * 領域内の総和を O(1) で求めて出力せよ。
 * - (H+1) x (W+1) の 1-indexed 2次元累積和配列 S を構築する。
 * - 包除原理により事前計算 O(HW)、クエリ O(1) を実現する。
 * 
 * 【制約】
 * - 1 <= H, W <= 1000
 * - 1 <= Q <= 2 * 10^5
 * - 1 <= r_1 <= r_2 <= H
 * - 1 <= c_1 <= c_2 <= W
 * - -10^9 <= A_{i, j} <= 10^9
 * 
 * 【入力例】
 * 3 4 2
 * 1 2 3 4
 * 5 6 7 8
 * 9 10 11 12
 * 1 1 2 2
 * 2 2 3 4
 * 
 * 【出力例】
 * 14
 * 54
 */

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int H, W, Q;
  cin >> H >> W >> Q;

  vector<vector<ll>> A(H, vector<ll>(W));
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      cin >> A[i][j];
    }
  }

  vector<vector<ll>> S(H + 1, vector<ll>(W + 1, 0));
  for (int i = 1; i <= H; ++i) {
    for (int j = 1; j <= W; ++j) {
      S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + A[i - 1][j - 1];
    }
  }

  for (int i = 0; i < Q; ++i) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    ll ans = S[r2][c2] - S[r1 - 1][c2] - S[r2][c1 - 1] + S[r1 - 1][c1 - 1];
    cout << ans << '\n';
  }

  return 0;
}