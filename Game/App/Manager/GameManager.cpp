#include "GameManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Scene/SceneBase.h"
#include "../Scene/Title.h"
#include "../Scene/Explanation.h"
#include "../Scene/Play.h"
#include "../Scene/Result.h"
#include "../Library/GamePad.h"
#include "../Library/Shadow.h"

namespace My3dApp
{
    // ゲームマネージャインスタンスへのポインタ定義
    GameManager* GameManager::instance = nullptr;

    SceneBase* GameManager::nowScene = nullptr;

    int GameManager::screenWidth;

    int GameManager::screenHeight;

    bool GameManager::fullScreen;

    int GameManager::score;

    int GameManager::combo;

    GameManager::GameManager()
    {
        // 画面の横幅初期化
        screenWidth = 0;

        // 画面の高さ初期化
        screenHeight = 0;

        // 非フルスクリーン
        fullScreen = false;
    }

    GameManager::~GameManager()
    {
        // 影管理用のインスタンス削除
        Shadow::DeleteInstance();
    }

    void GameManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new GameManager();
        }
    }

    void GameManager::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    bool GameManager::ProcessInput()
    {
        // エラーがでた、もしくはウィンドウが閉じられたら
        if (ProcessMessage() != 0)
        {
            // ループのフラグを倒す
            return false;
        }

        // ESCキーが押されたら
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            // ループのフラグを倒す
            return false;
        }

        return true;
    }

    int GameManager::Init()
    {
        // 画面の横幅を1920に設定
        screenWidth = 1920;

        // 画面の縦幅を1080に設定
        screenHeight = 1080;

        // 全画面にする
        fullScreen = true;

        // 全画面のフラグが立っていなければ
        if (!fullScreen)
        {
            // ウィンドウモードにする
            ChangeWindowMode(TRUE);
        }

        // 画面モードの設定
        SetGraphMode(screenWidth, screenHeight, 32);

        // DirectX11を使用するようにする
        SetUseDirect3DVersion(DX_DIRECT3D_11);

        // DxLibの初期化
        if (DxLib_Init() == -1)
        {
            return -1;
        }

        // Effekseerの初期化
        if (Effekseer_Init(8000) == -1)
        {
            DxLib_End();
            return -1;
        }

        // 影管理用のインスタンス生成
        Shadow::CreateInstance();

        // マウスカーソルを表示しない
        SetMouseDispFlag(false);

        // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
        SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

        // DXライブラリのデバイスロストした時のコールバックを設定する
        // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する
        Effekseer_SetGraphicsDeviceLostCallbackFunctions();

        // 描画先を裏に設定する
        SetDrawScreen(DX_SCREEN_BACK);

        // Zバッファを有効にする
        SetUseZBuffer3D(true);

        // Zバッファへの書き込みを有効にする
        SetWriteZBuffer3D(true);

        // 描画する奥行き方向の範囲を設定
        SetCameraNearFar(10.0f, 30000.0f);

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 80.0f, -200.0f), VGet(0.0f, 80.0f, 0.0f));

        // ライトの方向を設定
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        // シャドウマップが想定するライトの方向セット
        SetShadowMapLightDirection(Shadow::GetShadowMap(), VGet(-1.5f, -10.5f, 0.5f));

        // シャドウマップに描画する範囲を設定
        SetShadowMapDrawArea(Shadow::GetShadowMap(), VGet(-2000.0f, -1.0f, -2000.0f), VGet(2000.0f, 100.0f, 2000.0f));

        return 0;
    }

    void GameManager::Loop()
    {
        // ループフラグ
        bool gameLoop = true;

        // 現フレームのカウント
        LONGLONG nowCount = GetNowHiPerformanceCount();

        // 前フレームのカウント
        LONGLONG prevCount = nowCount;

        // 待機フレーム時間（60fps想定）
        // 1/60 = 1.66666...
        float waitFrameTime = 16667;

        SetBackgroundColor(135 , 206, 235);

        ResetScore();

        ResetCombo();

        // ループ本体
        while (gameLoop)
        {
            // 現フレームと前フレームとの差分
            float deltaTime;

            // 現フレームカウントの更新
            nowCount = GetNowHiPerformanceCount();

            // 差分を100万分の1にして保存する（マイクロ秒換算）
            deltaTime = (nowCount - prevCount) / 1000000.0f;

            // ゲームパッドの更新
            GamePad::Update();

            // ループ継続の確認
            gameLoop = ProcessInput();

            // 仮シーン
            SceneBase* tmpScene;

            // シーンの更新と現在のシーンの保存
            tmpScene = nowScene->Update(deltaTime);

            // 画面の初期化
            ClearDrawScreen();

            // シーンの描画
            nowScene->Draw();

            // fps確認用（後で消す）
            //SetFontSize(25);
            //DrawFormatString(200, 10, GetColor(255, 255, 255), "fps:%f", deltaTime);
            //DrawFormatString(200, 10, GetColor(255, 255, 255), "lightNum:%d", GetEnableLightHandleNum());

            // 裏画面の内容を表画面に反映させる
            ScreenFlip();

            // 更新前のシーンと更新後のシーンが異なったら
            if (nowScene != tmpScene)
            {
                // シーンを解放
                delete nowScene;

                // 新しいシーンを入れる
                nowScene = tmpScene;
            }

            if (!tmpScene)
            {
                break;
            }

            // 60fps制御用ループ
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            // 現在のカウントを保存する
            prevCount = nowCount;
        }

        // Effkseerの終了処理
        Effkseer_End();

        // DxLibの終了処理
        DxLib_End();
    }
}// namespace My3dApp