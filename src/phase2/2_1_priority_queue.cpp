/**
 * Phase 2.1: std::priority_queue の実践
 * 
 * 【問題】
 * 空の優先度付きキュー (最小ヒープ) を管理し、Q 個のクエリを処理する。
 * - 1 X: 整数 X をキューに追加。
 * - 2: 最小値を取り出して出力し削除 (空なら -1)。
 * - 3 K: 小さい方から最大 K 個取り出し、その総和を出力し削除 (空なら 0)。
 * 
 * 【制約】
 * - 1 <= Q <= 2 * 10^5
 * - 1 <= X <= 10^9
 * - 1 <= K <= 2 * 10^5
 * 
 * 【入力例】
 * 7
 * 1 30
 * 1 10
 * 1 20
 * 2
 * 1 5
 * 3 2
 * 2
 * 
 * 【出力例】
 * 10
 * 25
 * 30
 */

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int Q;
  cin >> Q;
  priority_queue<ll, vector<ll>, greater<ll>> pq;

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;

    if (type == 1) {
      ll x;
      cin >> x;
      pq.push(x);
    } else if (type == 2) {
      if (pq.empty()) {
        cout << -1 << "\n";
      } else {
        ll val = pq.top();
        pq.pop();
        cout << val << "\n";
      }
    } else {
      int K;
      cin >> K;
      ll sum = 0LL;
      for (int j = 0; j < K; j++) {
        if (pq.empty()) {
          break;
        }
        ll val = pq.top();
        sum += val;
        pq.pop();
      }
      cout << sum << "\n";
    }
  }

  return 0;
}