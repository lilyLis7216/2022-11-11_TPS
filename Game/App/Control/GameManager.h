#pragma once

namespace My3dApp
{
    /**
    * ゲームマネージャクラス
    */
    class GameManager final
    {
    private:
        /**
        * コンストラクタ
        *
        * シングルトン
        */
        GameManager();

        /** ループを抜ける際に使う入力処理関数*/
        bool ProcessInput();

        /** 画面横幅*/
        int screenWidth;

        /** 画面縦幅*/
        int screenHeight;

        /** 全画面フラグ*/
        bool fullScreen;

    public:
        /**
        * ゲームマネージャのインスタンス取得
        *
        * @return ゲームマネージャのインスタンス
        */
        static GameManager& Instance()
        {
            static GameManager gameSystem;
            return gameSystem;
        }

        /** デストラクタ*/
        ~GameManager() {};

        /** 初期化処理関数*/
        void Init();

        /** ゲームループ関数*/
        void Loop();
    };

    /** ゲームマネージャインスタンスのマクロ作成*/
    #define GameInstance GameManager::Instance()
}/** namespace My3dAppp*/