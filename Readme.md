# KyokoEngine

## アプリケーション
### 概要
* ジャンル : リズムゲーム
* プレイ人数 : 1人
* 制作人数 : 1人
* 制作環境 : DirectX12
・・ここｐんｇ
### こだわり
* アウトラインやブルーム、ライトのシェーダ
* オブジェクトの設置
* カメラのアニメーション

### アウトラインやブルーム、ライトのシェーダ
- 描画までの流れ
    * それぞれをレンダーターゲットに書き込む
        * アウトライン
        * ブルーム
        * ライト
        * そのまま
    * 書き込まれた色と深度のデータを１つのシェーダにまとめて送り深度比較をして書き込む
- アウトライン
    * 深度ベースでアウトラインを描画
    * 深度によってアウトラインの太さが変わる
- ブルーム
    * 横のガウシアンブラーをしたものを縦のガウシアンブラーをして、処理を軽くしている
    * レンダーターゲットのサイズを変更することができ、粗くして処理を軽くしている
- ライト
    * スポットライトの反射とビルボードを用いて表現している

### オブジェクトの設置
- 大まかな設計

- 特徴
    * パラメータの設定が容易
    * 描画のタイプの切り替え
    * インスタンシング描画
- パラメータの設定が容易
    * [GlobalVariable](#GlobalVariable)を用いて設定
    * 基底クラスの関数で設定の共通部分をまとめているので楽
- 描画のタイプの切り替え
    * [ObjectModelファイル]()にある.objを切り替えることができる
    * [タイプ](#アウトラインやブルーム、ライトのシェーダ)を切り替えられる
- インスタンシング描画
    * オブジェクトとタイプが一致しているものをまとめて描画するようにしている


### カメラのアニメーション
・・ここぎｆ

カメラに動きを付けたいけど、1曲分の動きを作るのは大変なので、vmdのカメラのアニメーションデータを読み込み、再生できるようにしました


## エンジン
- **使用可能なデータと用途**
    * Model (obj)
    * RigidAnimationModel (gltf)
    * SkinningAnimationModel (gltf)
    * Texture (png,jpeg,dds)
    * Audio (mp3,wav)
    * GlobalVariable (json)
    * CameraAnimation (vmd)
- **特徴**
    * [GlobalVariable](#GlobalVariable)
    * [Audio](#Audio)

### GlobalVariable
jsonデータへの保存や読み込み、ImGuiでの調整ができるようになっています。
- **設定できる型**
    * int (ImGui::DragInt)
    * float (ImGui::DragFloat)
    * Vector2 (ImGui::DragFloat2)
    * Vector3 (ImGui::DragFloat3)
    * Vector4 (ImGui::DragFloat4)
    * bool (ImGui::Checkbox)
    * std::string (ImGui::Text)
- **設定できる項目**
    * 上記の型のデフォルト設定
    * Color (ImGui::ColorEdit4)
    * Combo (ImGui::Combo)
    * ComboName (ImGui::Text)

![GlobalVariableの設定](https://github.com/MizukamiKotaro/KyokoEngine/blob/master/githubResources/kyokoGlobal.png)

- **特徴**
    * ImGuiをtreeで表示されるようにしたため、クラスや用途によってまとめることが可能
    * treeが開いているかの情報の取得
    * 調整を必要としないデータの保存や上書きが可能
    * 表示するImGuiのタイトルバーの選択
    * 終了時の状態を保存
- **使用例**
    * ステージエディターに拡張
    * 音量設定やクリア状況といったプレイデータの保存
    * Modelデータの格納場所から自動でComboNameを作成し、Comboで表示したいModelデータの選択と保存


### Audio
音声データの読み込み、再生、停止、ループ、一時停止の基本的な機能の他以下のような機能があります。
* 全体のボリュームと、SE全体のボリューム、Music全体のボリュームをImGuiでの調整、保存
* データの格納場所(Resources/AudioのSEかMusicフォルダ)によってSEかMusicのボリュームに影響されるかを自動で判別
* 全体のボリュームの他に、使用したい用途でタグを設定して個々のボリュームのImGuiでの調整、保存
* ボリュームの調整用の音の再生と停止ImGuiのボタン表示

全体のボリュームは自動で調整できるように設定しています。

その他は読み込み関数Load(const std::string& filename, const std::string& tag = "_", float volume = 0.7f)
を呼び出すと自動的に設定され調整できるようになります。

![AudioのImGui](https://github.com/MizukamiKotaro/KyokoEngine/blob/master/githubResources/audio.gif)

**この2つの特徴はチーム制作でとても好評でした。**

## 外部ライブラリ
* [Assimp](https://github.com/assimp/assimp)
* [DirectXTex](https://github.com/microsoft/DirectXTex)
* [ImGui](https://github.com/ocornut/imgui)
* [nlohmann](https://github.com/nlohmann/json)
