#pragma once

namespace My3dApp
{
    /**
    * ゲームマネージャクラス
    */
    class GameManager final
    {
    private:
        /** コンストラクタ*/
        GameManager();

        /** デストラクタ*/
        ~GameManager();

        /** 初期化処理関数*/
        void Init();

        /** ループを抜ける際に使う入力処理関数*/
        static bool ProcessInput();

        /** マネージャのインスタンス*/
        static GameManager* instance;

        /** シーン*/
        static class SceneBase* nowScene;

        /** 画面横幅*/
        int screenWidth;

        /** 画面縦幅*/
        int screenHeight;

        /** 全画面フラグ*/
        bool fullScreen;

    public:
        /** インスタンスの生成*/
        static void CreateInstance();

        /** インスタンスの削除*/
        static void DeleteInstance();

        /** 始めるシーンの指定*/
        static void SetFirstScene(SceneBase* scene) { nowScene = scene; }

        /** ゲームループ関数*/
        static void Loop();
    };
}/** namespace My3dAppp*/