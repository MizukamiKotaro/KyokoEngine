# KyokoEngine
## エンジン
- 自分で書いていないコード
    * assimp(obj,gltfの読み込み)
    * DirectXTex(textureの読み込み、生成)
    * imgui(エディター)
    * nlohmann(jsonデータの読み込み、書き出し)
- 使用可能なデータと用途
    * Model (obj)
    * RigidAnimationModel (gltf)
    * SkinningAnimationModel (gltf)
    * Texture (png,jpeg,dds)
    * Audio (mp3,wav)
    * GlobalVariable (json)
    * CameraAnimation (vmd)
- エンジンの特徴
    * Audio
    * GlobalVariable
### Audio
音声データの読み込み、再生、停止、ループ、一時停止の基本的な機能の他以下のような機能があります。
* 全体のボリュームと、SE全体のボリューム、Music全体のボリュームをImGuiでの調整、保存
* データの格納場所(Resources/AudioのSEかMusicフォルダ)によってSEかMusicのボリュームに影響されるかを自動で判別
* 全体のボリュームの他に、使用したい用途でタグを設定して個々のボリュームのImGuiでの調整、保存
* ボリュームの調整用の音の再生と停止ImGuiのボタン表示

全体のボリュームは自動で調整できるように設定しています。

その他は読み込み関数Load(const std::string& filename, const std::string& tag = "_", float volume = 0.7f)
を呼び出すと自動的に設定され調整できるようになります。


### GlobalVariable
jsonデータへの保存や読み込み、ImGuiでの調整ができるようになっています。
- 設定できる型
    * int (ImGui::DragInt)
    * float (ImGui::DragFloat)
    * Vector2 (ImGui::DragFloat2)
    * Vector3 (ImGui::DragFloat3)
    * Vector4 (ImGui::DragFloat4)
    * bool (ImGui::Checkbox)
    * std::string (ImGui::Text)
- 設定できる項目
    * 上記の型のデフォルト設定
    * Color (ImGui::ColorEdit4)
    * Combo (ImGui::Combo)
    * ComboName (ImGui::Text)
- 特徴
    * ImGuiをtreeで表示されるようにしたため、クラスや用途によってまとめることが可能
    * 調整を必要としないデータの保存や上書きが可能
    * 表示するImGuiのタイトルバーの選択
    * 終了時の状態を保存
- 使用例
    * 上記のAudioの保存
    * ステージエディターに拡張
    * 音量設定やクリア状況といったプレイデータの保存
    * Modelデータの格納場所から自動でComboNameを作成し、Comboで表示したいModelデータの選択と保存


