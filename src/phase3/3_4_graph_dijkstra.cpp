/**
 * Phase 3.4: グラフ探索と最短経路（ダイクストラ法）
 * 
 * 【問題】
 * N 頂点 M 辺の重み付き有向グラフが与えられる（頂点番号は 0 から N-1）。
 * 各辺 i は頂点 u_i から v_i へ重み c_i を持つ。
 * 頂点 0 を始点として、各頂点 i (0 <= i < N) への最短距離を出力せよ。
 * 到達不能な頂点については -1 を出力せよ。
 * 
 * 【制約】
 * - 1 <= N <= 10^5
 * - 0 <= M <= 2 * 10^5
 * - 0 <= u_i, v_i < N
 * - 1 <= c_i <= 10^9
 * 
 * 【入力例 1】
 * 4 5
 * 0 1 10
 * 0 2 5
 * 2 1 2
 * 1 3 1
 * 2 3 9
 * 
 * 【出力例 1】
 * 0
 * 7
 * 5
 * 8
 * 
 * 【入力例 2 (到達不能な頂点を含む場合)】
 * 5 4
 * 0 1 10
 * 0 2 5
 * 2 1 2
 * 1 3 1
 * 
 * 【出力例 2】
 * 0
 * 7
 * 5
 * 8
 * -1
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

constexpr ll INF = 1LL << 60;

struct Edge {
  int to;
  ll cost;
};

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  vector<vector<Edge>> G(N);

  for (int i = 0; i < M; i++) {
    int u, v;
    ll c;
    cin >> u >> v >> c;
    // 入力値は0-indexedなので、u, vはそのままでOK.
    G[u].push_back({v, c});
  }

  // 頂点0からの距離
  vector<ll> dist(N, INF);
  using P = pair<ll, int>;
  priority_queue<P, vector<P>, greater<P>> pq;
  dist[0] = 0;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue;

    for (const auto &edge : G[u]) {
      if (dist[u] + edge.cost < dist[edge.to]) {
        dist[edge.to] = dist[u] + edge.cost;
        pq.push({dist[edge.to], edge.to});
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (dist[i] == INF) {
      cout << -1 << '\n';
    } else {
      cout << dist[i] << '\n';
    }
  }

  return 0;
}