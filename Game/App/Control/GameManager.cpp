#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"
#include "../Sequence/SceneBase.h"
#include "../Sequence/Title.h"
#include "../Sequence/StageSelect.h"

namespace My3dApp
{
    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
        Init();
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

    /**
    * 新しくシーンを生成する関数
    * 後ほど修正予定
    */
    SceneBase* CreateScene(SceneType now)
    {
        /** 返すシーン*/
        SceneBase* retScene = nullptr;
        switch (now)
        {
        case SceneType::Scene_Title:
            retScene = new Title();
            break;
        case SceneType::Scene_StageSelect:
            retScene = new StageSelect();
            break;
        case SceneType::Scene_Play:
            break;
        case SceneType::Scene_Result:
            break;
        case SceneType::Scene_Exit:
            break;
        default:
            break;
        }

        return retScene;
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
        float waitFrameTime = 15900;

        /** シーンの生成*/
        SceneBase* scene = new Title();

        /** 現在のシーンタイプ*/
        SceneType nowSceneType = SceneType::Scene_Title;

        /** 前のシーンタイプ*/
        SceneType prevSceneType = nowSceneType;

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

            /** シーンの更新と現在のシーンタイプの保存*/
            nowSceneType = scene->Update();

            /** 画面の初期化*/
            ClearDrawScreen();

            /** シーンの描画*/
            scene->Draw();

            /** fps確認用（後で消す）*/
            DrawFormatString(100, 100, GetColor(255, 255, 255), "fps:%f", deltaTime);

            /** 裏画面の内容を表画面に反映させる*/
            ScreenFlip();

            /** 現在のシーンと前のシーンが異なったら*/
            if (nowSceneType != prevSceneType)
            {
                /** シーンがあれば*/
                if (scene)
                {
                    /** シーンを解放*/
                    delete scene;

                    /** シーンをnullptrに設定する*/
                    scene = nullptr;
                }

                /** 現在のシーンを新しく作ってシーンに入れる*/
                scene = CreateScene(nowSceneType);
            }

            /** 60fps制御用ループ*/
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            /** 現在のシーンタイプを保存する*/
            prevSceneType = nowSceneType;

            /** 現在のカウントを保存する*/
            prevCount = nowCount;
        }

        /** シーンの解放*/
        delete scene;

        /** DxLibの使用終了処理*/
        DxLib_End();
    }

}/** namespace My3dApp*/
