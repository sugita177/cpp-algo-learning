# 2.3 座標圧縮の実装パイプライン

## 1. 座標圧縮とは？（動機と写像の考え方）

競技プログラミングにおいて、「値の範囲が $-10^9 \le X_i \le 10^9$ のように巨大だが、登場する要素数 $N$ は $10^5$ 程度」という問題が頻出する。

### なぜそのままではダメなのか？
- $10^9$ のサイズを持つ配列を確保しようとすると、メモリが数 GB 必要になり **確実に MLE（メモリ制限超過）** となる。
- 負の数（$-100$ 等）は配列のインデックスとして直接使えない。

### 座標圧縮の威力
大小関係を保ったまま、巨大な値を **$0 \le C_i < N$ のコンパクトな連続整数に変換（写像）** する。
これにより、要素数 $N$ の通常の配列、累積和テーブル、セグメント木などのインデックスとして扱えるようになる。

---

## 2. 実装パイプライン（4つのステップ）

```mermaid
graph LR
    A[元配列 A] -->|コピー| B[vals]
    B -->|1. sort| C[昇順ソート]
    C -->|2. unique| D[重複を先頭に寄せる]
    D -->|3. erase| E[ゴミ要素を削除]
    E -->|4. lower_bound| F[圧縮インデックス取得]
```

### Step 1: ソート (`std::sort`)
`unique` は **「隣り合う重複」** しか検知できないため、必ず事前に昇順ソートを行う。

### Step 2 & 3: 重複排除 (`unique` + `erase` イディオム)
```cpp
vals.erase(unique(vals.begin(), vals.end()), vals.end());
```
- **`unique` の動作**: 重複しない要素を前方に詰め、**「有効なユニーク範囲の終端（半開区間の `end`）」を指すイテレータ** を返す（後ろに残った要素はゴミデータとして放置される）。
- **`erase` の動作**: 半開区間 `[new_end, vals.end())` を物理削除し、`vals` のサイズを真のユニーク要素数まで縮小する。

### Step 4: 圧縮後座標の取得 (`std::lower_bound`)
元の値 $A_i$ が `vals` の中で何番目に位置するかを二分探索で求める。
```cpp
int c = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
```
`vals` はソート済みかつランダムアクセスイテレータなので、1 回あたり **$O(\log N)$**、全体で **$O(N \log N)$** で変換が完了する。

---

## 3. 元の値の復元（$O(1)$）

圧縮後の座標 $c$（$0 \le c < \text{vals.size()}$）から元の値を復元したい場合は、単に `vals[c]` を参照するだけで **$O(1)$** で取り出せる。

---

## 4. 実戦テクニック: 三項演算子による空白・改行出力

配列の要素を空白区切りで出力し、末尾のみ改行したい場合、`ssize` と三項演算子を組み合わせることで `size - 1` のアンダーフローを起こさず安全・簡潔に記述できる。

```cpp
for (int i = 0; i < ssize(v); i++) {
    cout << v[i] << (i == ssize(v) - 1 ? "\n" : " ");
}
```

---

## 5. 実践コード

```cpp
/**
 * Phase 2.3: 座標圧縮の実装パイプライン
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

  // 1. sort -> unique -> erase パイプライン
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());

  // 2. 二分探索で圧縮座標に変換
  vector<int> C(N);
  for (int i = 0; i < N; i++) {
    C[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
  }

  // 3. 圧縮後の数列を出力
  for (int i = 0; i < N; i++) {
    cout << C[i] << (i == N - 1 ? "\n" : " ");
  }

  // 4. ユニーク要素数を出力
  cout << vals.size() << '\n';

  // 5. 復元テーブル (vals) を出力
  for (int i = 0; i < ssize(vals); i++) {
    cout << vals[i] << (i == ssize(vals) - 1 ? "\n" : " ");
  }

  return 0;
}
```
