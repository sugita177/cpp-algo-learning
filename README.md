# C++ Competitive Programming Learning

競技プログラミング（AtCoder 等）に向けた C++（C++20）の再定着・自力実装力強化のための学習リポジトリです。

詳細なカリキュラムと進捗管理は [LEARNING_PLAN.md](LEARNING_PLAN.md) を参照してください。

---

## 方針・目的

- **自力実装力の定着**: AI メンターの指導のもと、完成コードを見ずに仕様と要件から自力で考察・実装する。
- **堅牢なコード設計**: 未定義動作（UB）、配列外参照、型オーバーフロー、イテレータ無効化を未然に防ぐ。
- **計算量・メモリ効率の意識**: $O(N)$ と $O(\log N)$ の違い、値渡しによるコピーコスト TLE などを徹底排除する。

---

## 技術スタック & ツール

- **言語**: C++20
- **コンパイラ**: GCC / Clang
- **テストツール**: [online-judge-tools](https://github.com/online-judge-tools/oj) (`oj`)
- **デバッグ**: GDB / LLDB, 各種サニタイザ（ASan / UBSan / `_GLIBCXX_DEBUG`）

---

## ディレクトリ構成

```text
.
├── README.md               # プロジェクト概要・コマンド集（本ファイル）
├── LEARNING_PLAN.md        # 学習計画書・カリキュラム進捗管理
├── .gitignore              # 実行ファイル・テストケース等の一時ファイル除外
├── templates/              # 競技プログラミング用テンプレート
│   └── template.cpp        # 基本テンプレート
├── src/                    # 演習・課題コード
│   ├── phase1/             # 基礎構文・STL・メモリモデル
│   ├── phase2/             # 典型データ構造・標準アルゴリズム
│   ├── phase3/             # 頻出アルゴリズム・UB耐性
│   └── phase4/             # 実践演習・デバッグワークフロー
└── notes/                  # 学んだ知見・落とし穴・振り返りメモ
```

---

## コマンドリファレンス

### 1. コンパイル

#### 通常ビルド（提出用高速化オプション）
```bash
g++ -std=gnu++20 -O2 -Wall -Wextra src/phase1/1_1_io.cpp -o a.out
```

#### デバッグ用ビルド（サニタイザ & GLIBCXX_DEBUG 有効化）
未定義動作、配列外参照、メモリリークを即座に検知します。**演習時はこのオプションを推奨**します。
```bash
g++ -std=gnu++20 -O0 -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG -Wall -Wextra src/phase1/1_1_io.cpp -o a.out
```

### 2. online-judge-tools (`oj`) の活用

```bash
# サンプルケースのダウンロード（例: ABC300 A問題）
oj dl https://atcoder.jp/contests/abc300/tasks/abc300_a

# サンプルに対するテスト実行
oj test -c ./a.out
```

---

## 学習の進め方

1. [LEARNING_PLAN.md](LEARNING_PLAN.md) から取り組むトピックを選択し、メンターに宣言する。
2. メンターから提示された「問い」や「ミニ課題」を考察し、`src/` 配下に実装する。
3. サニタイザ付きビルドで動作検証を行い、メンターへレビューを依頼する。
4. レビューを通過したら、[LEARNING_PLAN.md](LEARNING_PLAN.md) の該当項目にチェックを入れる。
