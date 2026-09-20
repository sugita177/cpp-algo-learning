/**
 * Phase 1.3: ペア・タプル・構造化束縛
 * 
 * 【問題】
 * 2次元平面上の N 個の点 (X, Y) と名前 S が与えられる。
 * 1. (X 昇順 -> Y 昇順 -> S 辞書順) でソートする。
 * 2. 参照の構造化束縛 (auto&) を用いて、全要素の Y 座標を 2 倍に更新する。
 * 3. const 参照の構造化束縛 (const auto&) を用いて、全要素を出力する。
 * 
 * 【入力例】
 * 4
 * 2 5 apple
 * 1 8 banana
 * 2 3 orange
 * 2 5 grape
 * 
 * 【出力例】
 * 1 16 banana
 * 2 6 orange
 * 2 10 apple
 * 2 10 grape
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

  sort(vec.begin(), vec.end());
  for (auto &[x, y, s] : vec) {
    y *= 2;
  }
  for (const auto &[x, y, s] : vec) {
    cout << x << " " << y << " " << s << '\n';
  }

  return 0;
}