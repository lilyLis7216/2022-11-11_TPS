#pragma once

namespace My3dApp
{
    /**
    * ゲームマネージャクラス
    */
    class GameManager final
    {
    private:
        /** ループを抜ける際に使う入力処理関数*/
        bool ProcessInput();

        /** 画面横幅*/
        int screenWidth;

        /** 画面縦幅*/
        int screenHeight;

        /** 全画面フラグ*/
        bool fullScreen;

    public:
        /** コンストラクタ*/
        GameManager();

        /** デストラクタ*/
        ~GameManager() {};

        /** 初期化処理関数*/
        void Init();

        /** ゲームループ関数*/
        void Loop();
    };

}/** namespace My3dAppp*/