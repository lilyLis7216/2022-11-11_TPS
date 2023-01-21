#pragma once

namespace My3dApp
{
    /// <summary>
    /// ゲームマネージャ
    /// </summary>
    class GameManager final
    {
    private:
        /// <summary>
        /// コンストラクタ（シングルトン）
        /// </summary>
        GameManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~GameManager();

        /// <summary>
        /// ループを抜ける際に使う入力処理関数
        /// </summary>
        /// <returns>ループ継続ならtrue そうでなければfalse</returns>
        static bool ProcessInput();

        // ゲームマネージャの唯一のインスタンス
        static GameManager* instance;

        // 現在のシーン
        static class SceneBase* nowScene;

        // 画面横幅
        static int screenWidth;

        // 画面縦幅
        static int screenHeight;

        // 全画面フラグ
        static bool fullScreen;

    public:
        /// <summary>
        /// インスタンスの生成
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// インスタンスの削除
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// 初期化処理
        /// </summary>
        static int Init();

        /// <summary>
        /// 最初のシーンの設定
        /// </summary>
        /// <param name="scene">最初に表示したいシーン</param>
        static void SetFirstScene(SceneBase* scene) { nowScene = scene; }

        /// <summary>
        /// ゲームループ
        /// </summary>
        static void Loop();

    };
}// namespace My3dApp