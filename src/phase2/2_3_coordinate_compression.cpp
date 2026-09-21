/**
 * Phase 2.3: 座標圧縮の実装パイプライン
 * 
 * 【問題】
 * 長さ N の数列 A が与えられる。
 * 1. sort -> unique -> erase のパイプラインで重複のない昇順配列 vals を作成する。
 * 2. 各要素 A_i について、vals における 0-indexed インデックス (圧縮後座標 C_i) を lower_bound で求める。
 * 3. 1 行目に圧縮後の数列 C を空白区切りで出力する。
 * 4. 2 行目に圧縮後のユニーク要素数 vals.size() を出力する。
 * 5. 3 行目に復元テーブル vals の全要素を空白区切りで出力する。
 * 
 * 【制約】
 * - 1 <= N <= 10^5
 * - -10^9 <= A_i <= 10^9
 * 
 * 【入力例】
 * 5
 * 50 -100 50 1000000000 -100
 * 
 * 【出力例】
 * 1 0 1 2 0
 * 3
 * -100 50 1000000000
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N;
  vector<int> a(N), vals(N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    vals[i] = a[i];
  }

  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  vector<int> C(N);
  for (int i = 0; i < N; i++) {
    C[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
  }

  for (int i = 0; i < N; i++) {
    cout << C[i] << (i == N - 1 ? "\n" : " ");
  }

  cout << vals.size() << '\n';

  for (int i = 0; i < ssize(vals); i++) {
    cout << vals[i] << (i == ssize(vals) - 1 ? "\n" : " ");
  }

  return 0;
}