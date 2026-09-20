/**
 * Phase 1.4: イテレータの仕組みと区間概念
 * 
 * 【問題】
 * ソート済み配列 A (要素数 N) と Q 個のクエリ X が与えられる。
 * 各クエリに対し、lower_bound を用いて X 以上の最初の要素を指すイテレータ it を取得し、以下を出力する:
 * 1. 要素の 0-indexed インデックス (存在しない場合は -1)
 * 2. 要素の値 (存在しない場合は -1)
 * 3. 1つ前の要素の値 (it が先頭の場合または存在しない場合は -1)
 * 
 * 【制約】
 * - 1 <= N, Q <= 10^5
 * - 1 <= A_i, X <= 10^9
 * 
 * 【入力例】
 * 5 4
 * 2 5 8 10 15
 * 5
 * 1
 * 12
 * 20
 * 
 * 【出力例】
 * 1 5 2
 * 0 2 -1
 * 4 15 10
 * -1 -1 -1
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < Q; i++) {
    int X;
    cin >> X;
    auto it = lower_bound(A.begin(), A.end(), X);
    if (it == A.end()) {
      cout << -1 << " " << -1 << " " << -1 << '\n';
    } else {
      int idx = it - A.begin();
      int val = *it;
      int prev = (idx > 0) ? A[idx - 1] : -1;
      cout << idx << " " << val << " " << prev << '\n';
    }
  }

  return 0;
}