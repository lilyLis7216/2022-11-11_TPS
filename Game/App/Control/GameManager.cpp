#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"

namespace My3dApp
{
    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
    }

    bool GameManager::ProcessInput()
    {
        /** エラーがでた、もしくはウィンドウが閉じられたら*/
        if (ProcessMessage() != 0)
        {
            /** ループのフラグを倒す*/
            return false;
        }

        /** エスケープキーが押されたら*/
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            /** ループのフラグを倒す*/
            return false;
        }

        return true;
    }

    void GameManager::Init()
    {
        /** 画面の横幅を1920に設定*/
        screenWidth = 1920;

        /** 画面の縦幅を1080に設定*/
        screenHeight = 1080;

        /** 全画面にする*/
        fullScreen = true;

        /** 全画面のフラグが立っていないとき*/
        if (!fullScreen)
        {
            ChangeWindowMode(TRUE);
        }

        /** 画面モードの設定*/
        SetGraphMode(screenWidth, screenHeight, 32);

        /** DxLibの初期化処理*/
        DxLib_Init();

        /** マウスカーソルを表示しない*/
        SetMouseDispFlag(false);
    }

    void GameManager::Loop()
    {
        /** ループフラグ*/
        bool gameLoop = true;

        /** 現フレームのカウント*/
        LONGLONG nowCount = GetNowHiPerformanceCount();

        /** 前フレームのカウント*/
        LONGLONG prevCount = nowCount;

        /**
        * 待機フレーム時間（60fps想定）
        * 1/60 = 1.66666...
        * 16000マイクロ秒 = 16ミリ秒 = 0.016秒
        */
        float waitFrameTime = 15500;

        /** ループ本体*/
        while (gameLoop)
        {
            /** 現フレームと前フレームとの差分*/
            float deltaTime;

            /** 現フレームカウントの更新*/
            nowCount = GetNowHiPerformanceCount();

            /** 差分を100万分の1にして保存する（マイクロ秒換算）*/
            deltaTime = (nowCount - prevCount) / 1000000.0f;

            /** ループ継続の確認*/
            gameLoop = ProcessInput();

            /** 画面の初期化*/
            ClearDrawScreen();

            /** 裏画面の内容を表画面に反映させる*/
            ScreenFlip();

            /** 60fps制御用ループ*/
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            /** ループが終わる直前に前フレームカウントの更新をする*/
            prevCount = nowCount;
        }

        /** DxLibの使用終了処理*/
        DxLib_End();
    }
}
