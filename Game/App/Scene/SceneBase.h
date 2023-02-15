#pragma once

namespace My3dApp
{
    /// <summary>
    /// シーンベース（基底クラス）
    /// </summary>
    class SceneBase
    {
    protected:
        // シーン表示用
        const char* text;

        int bgImage;

        int nextScene;

        int alpha;

        const int fadeSpeed = 2;

        enum NextScene
        {
            TITLE = 0,
            CONTROLS,
            PLAY,
            RESULT,
            QUIT,
        };

        int fadeState;

        enum FadeState
        {
            FADE_NONE = 0,
            FADE_OUT,
            FADE_IN,
        };

        void FadeIn();

        void FadeOut();

        void SetAlpha(int set) { alpha = set; }

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        SceneBase();

        /// <summary>
        /// 仮想デストラクタ
        /// </summary>
        virtual ~SceneBase();

        /// <summary>
        /// シーンベースの更新（純粋仮想関数）
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        virtual SceneBase* Update(float deltaTime) = 0;

        /// <summary>
        /// シーンの描画（純粋仮想関数）
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// シーン切り替えの入力
        /// </summary>
        /// <param name="sceneNum">遷移したいシーン</param>
        /// <returns></returns>
        SceneBase* CheckRetScene(int sceneNum);

        // 以下デバッグ用関数

        /// <summary>
        /// 現在のシーンの確認用
        /// </summary>
        void CheckNowScene();

    };
}// namespace My3dApp