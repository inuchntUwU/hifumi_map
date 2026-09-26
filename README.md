# hifumi agent keymap

[hifumi](https://github.com/qmk/qmk_firmware/tree/master/keyboards/hifumi)（QMK 対応の 6 キーマクロパッド / Pro Micro）を、CLI AI エージェントの共通操作用キーボードにするキーマップです。

対象: **Claude Code / Codex CLI / opencode / pi**

## 目的

CLI AI エージェントを使っていると、「中断」「承認・送信」「選択肢の上下移動」「モード切替」「音声入力」といった操作を何度も繰り返します。これらを 6 キーにまとめ、どのエージェントでも同じ手の動きで操作できるようにするのが目的です。

## キー配列

### 通常時

|        | 左                            | 中  | 右                          |
| ------ | ----------------------------- | --- | --------------------------- |
| **上** | Esc（中断。長押しで FN）      | ↑   | Enter（承認・送信）         |
| **下** | Shift+Tab（モード切替）       | ↓   | Win+H（Windows の音声入力） |

### FN（左上を押している間。LED がオレンジになる）

|        | 左         | 中         | 右                        |
| ------ | ---------- | ---------- | ------------------------- |
| **上** | （押下中） | ホイール↑  | Ctrl+C                    |
| **下** | Tab        | ホイール↓  | QK_BOOT（書き込みモード） |

- ホイールスクロールは読みやすいようにゆっくりめに設定しています（`config.h`）。
- FN を離すと LED は元の設定に戻ります。

## ファイル構成

```
keymaps/agent/
├── keymap.c   # キーマップ本体
├── rules.mk   # MOUSEKEY_ENABLE（ホイール用）
└── config.h   # ホイールスクロール速度の調整
```

## ビルドと書き込み

1. [QMK の環境](https://docs.qmk.fm/newbs_getting_started)を用意し、`qmk setup` で `qmk_firmware` を取得します。
2. このリポジトリの `keymaps/agent/` にある 3 ファイルを、`qmk_firmware` の `keyboards/hifumi/keymaps/agent/` に置きます。

   ```sh
   mkdir -p ~/qmk_firmware/keyboards/hifumi/keymaps/agent
   cp keymaps/agent/* ~/qmk_firmware/keyboards/hifumi/keymaps/agent/
   ```

3. 書き込みます。

   ```sh
   qmk flash -kb hifumi -km agent
   ```

   `Waiting for USB serial port...` と表示されたら、下記の方法で hifumi を書き込みモードにしてください。

ビルドだけなら `qmk compile -kb hifumi -km agent` で `hifumi_agent.hex` が生成されます。

### GitHub Actions でのビルド

push するたびに GitHub Actions がファームウェアをビルドします。Actions の実行結果ページから artifact（`hifumi_agent.hex`）をダウンロードして、QMK Toolbox などで書き込むこともできます。

## 書き込みモード

- **このキーマップを書き込み済みの場合**: 左上を押したまま右下を押すと書き込み待ち（ブートローダー）になります。Pro Micro のブートローダーは Caterina なので、約 8 秒で通常状態に戻ります。その間に書き込みを開始してください。
- **初回（別のファームウェアが入っている場合）**: Pro Micro の **RST と GND をショート**すると書き込み待ちになります（こちらも約 8 秒）。

## ライセンス

[GPL-2.0-or-later](LICENSE)（QMK の hifumi default キーマップに合わせています）
