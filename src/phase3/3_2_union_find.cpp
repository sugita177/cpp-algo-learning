/**
 * Phase 3.2: 素集合データ構造 (Union-Find)
 * 
 * 【問題】
 * N 頂点 (0-indexed: 0 ~ N-1) の素集合データ構造を管理し、Q 個のクエリを処理する。
 * - 0 u v: u と v のグループを結合する (unite)。
 * - 1 u v: u と v が同じグループに属するか判定する (is_same)。同じなら Yes、異なるなら No。
 * - 2 u: u が属するグループの要素数を出力する (size)。
 * 
 * 【制約】
 * - 1 <= N, Q <= 2 * 10^5
 * - 0 <= u, v < N
 * 
 * 【入力例】
 * 5 7
 * 0 0 1
 * 0 1 2
 * 1 0 2
 * 1 0 3
 * 2 0
 * 0 3 4
 * 0 1 4
 * 
 * 【出力例】
 * Yes
 * No
 * 3
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct UnionFind {
  vector<int> par;

  // コンストラクタ: 全員を -1 (サイズ1の根) で初期化
  UnionFind(int n) : par(n, -1) {}

  int root(int x) {
    // 負数の場合は自分が根なのでxをそのまま返す
    if (par[x] < 0)
      return x;
    // 根でない場合は親を再起的に辿っていく
    return par[x] = root(par[x]);
  }

  // 同じグループかの判定
  bool is_same(int x, int y) { return root(x) == root(y); }

  // 結合する
  bool unite(int x, int y) {
    // 親の取得
    x = root(x);
    y = root(y);

    // 同じグループの場合、falseを返す
    if (x == y)
      return false;

    // xをサイズの大きいグループにするため、swap
    if (-par[x] < -par[y])
      swap(x, y);

    // xにyを併合する
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  // サイズの取得
  int size(int x) { return -par[root(x)]; }
};

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;
  UnionFind uf(N);

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;
    if (type == 0) {
      int u, v;
      cin >> u >> v;
      uf.unite(u, v);
    } else if (type == 1) {
      int u, v;
      cin >> u >> v;
      if (uf.is_same(u, v)) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    } else {
      int u;
      cin >> u;
      cout << uf.size(u) << '\n';
    }
  }

  return 0;
}