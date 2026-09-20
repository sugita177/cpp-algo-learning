/**
 * Phase 1.5: 参照渡し・コピーコスト・符号なし型の罠
 * 
 * 【問題】
 * 整数 N と N 個の要素からなる配列 A が与えられる (N=0, 1 の場合あり)。
 * 1. modify_elements(vector<ll>& v):
 *    各要素について、偶数なら 2 で割り、奇数なら 3 倍に直接書き換える。
 * 2. print_adjacent_diffs(const vector<ll>& v):
 *    隣接する 2 要素の差の絶対値 |v_i - v_{i+1}| を順に出力する。
 *    N <= 1 の場合はアンダーフローを起こさず何も出力しないこと。
 * 
 * 【制約】
 * - 0 <= N <= 10^5
 * - 1 <= A_i <= 10^9
 * 
 * 【入力例 1】
 * 4
 * 6 5 8 3
 * 
 * 【出力例 1】
 * 12
 * 11
 * 5
 * 
 * 【入力例 2 (エッジケース)】
 * 1
 * 10
 * (出力なし)
 */

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void modify_elements(vector<ll> &v) {
  for (auto &x : v) {
    if (x % 2 == 0) {
      x /= 2;
    } else {
      x *= 3;
    }
  }
}

void print_adjacent_diffs(const vector<ll> &v) {
  for (int i = 0; i < ssize(v) - 1; i++) {
    cout << abs(v[i + 1] - v[i]) << '\n';
  }
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N;
  vector<ll> a(N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  modify_elements(a);
  print_adjacent_diffs(a);

  return 0;
}