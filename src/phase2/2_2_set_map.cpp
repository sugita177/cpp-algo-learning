/**
 * Phase 2.2: 平衡二分探索木コンテナ (set, multiset, map)
 * 
 * 【問題】
 * multiset<int> と map<string, int> を管理し、Q 個のクエリを処理する。
 * - 1 X: マルチセットに整数 X を追加。
 * - 2 X: マルチセットから整数 X を 1 つだけ削除 (存在しない場合は何もしない)。
 * - 3 X: マルチセット内で X 以上の最小値を出力 (存在しない場合は -1)。
 * - 4 S: 単語 S の現在の出現回数を出力し、その後出現回数を +1 する。
 * 
 * 【制約】
 * - 1 <= Q <= 2 * 10^5
 * - 1 <= X <= 10^9
 * - S は長さ 1 以上 10 以下の英小文字
 * 
 * 【入力例】
 * 9
 * 1 10
 * 1 20
 * 1 10
 * 3 10
 * 2 10
 * 3 10
 * 3 25
 * 4 apple
 * 4 apple
 * 
 * 【出力例】
 * 10
 * 10
 * -1
 * 0
 * 1
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  multiset<int> s;
  map<string, int> mp;

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;

    if (type == 1) {
      int x;
      cin >> x;
      s.insert(x);
    } else if (type == 2) {
      int x;
      cin >> x;
      auto it = s.find(x);
      if (it != s.end()) {
        s.erase(it);
      }
    } else if (type == 3) {
      int x;
      cin >> x;
      auto it = s.lower_bound(x);
      if (it != s.end()) {
        cout << *it << "\n";
      } else {
        cout << -1 << "\n";
      }
    } else {
      string S;
      cin >> S;
      if (mp.contains(S)) {
        cout << mp[S] << "\n";
        mp[S]++;
      } else {
        cout << 0 << "\n";
        mp[S] = 1;
      }
    }
  }

  return 0;
}