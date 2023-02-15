#include "Play.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Manager/GameManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/EnemyManager.h"
#include "../Manager/AssetManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Map.h"
#include "../GameObject/Enemy/NormalEnemy.h"
#include "../Library/DebugGrid.h"
#include "../Library/UserInterface.h"
#include "../Library/GamePad.h"
#include "Title.h"
#include "Result.h"

namespace My3dApp
{
    int Play::gaugeValue = 0;

    Play::Play()
        : timer(60.0f)
        , prevComb(0)
        , startCount(4)
        , startCountTimer(4.0f)
        , countSE1(false)
        , endCount(11)
        , player(nullptr)
    {
        EnemyManager::CreateInstance();

        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        //GameObjectManager::Entry(new NormalEnemy(VGet(0, 200, 1000)));

        LoadDivGraph("../asset/image/num.png", 12, 6, 2, 64, 64, countImage);

        playerBar = LoadGraph("../asset/image/playerBar.png");

        // ライトの方向を設定
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        // ライトの座標を設定
        SetLightPosition(VGet(100.0f, -10.5f, -50.0f));

        // 遠近法カメラへ切り替え
        SetupCamera_Perspective(1000.0f);

        SetAlpha(255);

        fadeState = FADE_IN;

        gaugeValue = 0;
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();

        EnemyManager::DeleteInstance();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (fadeState == FADE_NONE && startCount > 0)
        {
            startCountTimer -= deltaTime;
            int prevStartCount = startCount;
            startCount = (int)startCountTimer;
            if (prevStartCount != startCount)
            {
                countSE1 = false;
            }
            if (!countSE1)
            {
                AssetManager::PlaySoundEffect("count1_1", false);
                countSE1 = true;
            }
        }
        else if (fadeState == FADE_NONE && startCount <= 0)
        {
            if (startCount == 0 && timer < 59.0f)
            {
                startCount = -1;
            }

            if (timer < 11.0f)
            {
                int prevEndCount = endCount;
                endCount = (int)timer;
                if (prevEndCount != endCount)
                {
                    countSE1 = false;
                }
                if (!countSE1)
                {
                    AssetManager::PlaySoundEffect("count1_1", false);
                    countSE1 = true;
                }
            }

            GamePad::SetPadUse(true);

            timer -= deltaTime;

            AssetManager::PlaySoundEffect("game", true);

            GameObjectManager::Update(deltaTime);

            GameObjectManager::Collision();

            EnemyManager::Update(deltaTime, timer, 7);

            GaugeUpdate(deltaTime);

            if (timer < 1)
            {
                timer = 0;
                endCount = 0;
                nextScene = RESULT;
                fadeState= FADE_OUT;
            }

            if (player->GetPos().y < -500.0f)
            {
                nextScene = RESULT;
                fadeState = FADE_OUT;
            }

            if (GamePad::GetButtonState(Button::BACK) == 1)
            {
                nextScene = TITLE;
                fadeState = FADE_OUT;
            }
        }
        else if (fadeState == FADE_OUT)
        {
            if (alpha <= 255)
            {
                AssetManager::StopAllSE();
                FadeOut();
                if (alpha >= 255)
                {
                    if (nextScene == RESULT)
                    {
                        retScene = new Result();
                    }
                    else if (nextScene == TITLE)
                    {
                        retScene = new Title();
                    }
                }
            }
        }
        else if (fadeState == FADE_IN)
        {
            GamePad::SetPadUse(false);

            GameObjectManager::Update(deltaTime);

            GameObjectManager::Collision();

            if (alpha > 0)
            {
                FadeIn();
                if (alpha <= 0)
                {
                    fadeState = FADE_NONE;
                }
            }
        }

        return retScene;
    }

    void Play::Draw()
    {
        GameObjectManager::Draw();

        DrawEffekseer3D();

        SetFontSize(50);

        // タイマーの表示
        UserInterface::UIBox(740, 1140, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(800, 70, GetColor(255, 255, 255), "Time:%0.1f", timer);

        // スコアの表示
        UserInterface::UIBox(1200, 1660, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(1240, 70, GetColor(255, 255, 255), "SCORE : %4.0f", (float)GameManager::GetScore());

        // コンボの表示
        UserInterface::UIBox(200, 660, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        int gaugeFillWidth = gaugeWidth * gaugeValue / gaugeMax;
        UserInterface::UIBox(gaugeX, gaugeX + gaugeFillWidth, gaugeY, gaugeY + gaugeHeight, 0, GetColor(255, 140, 0), 0);

        if (gaugeValue > 0)
        {
            UserInterface::UIText(220, 70, GetColor(255, 255, 255), "SCORE BONUS");
        }

        UserInterface::UIBox(768, 1152 , 880, 1010, 0, GetColor(0, 0, 0), 0);
        DrawRotaGraph(960, 950, 1.0f, 0, playerBar, TRUE);
        if (fadeState != FADE_IN && timer < 60.0f)
        {
            player->DamageParView(0);
        }

        if (startCount < 4 && startCount >= 1 && fadeState == FADE_NONE)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
            SetDrawMode(DX_DRAWMODE_BILINEAR);
            DrawRotaGraph(960, 540, 10.0f, 0, countImage[startCount], TRUE);
            SetDrawMode(DX_DRAWMODE_NEAREST);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }

        if (startCount == 0)
        {
            SetFontSize(200);
            UserInterface::UIText(600, 500, GetColor(255, 255, 255), "Start!");
        }

        if (endCount < 11 && endCount >= 1)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
            SetDrawMode(DX_DRAWMODE_BILINEAR);
            DrawRotaGraph(960, 540, 10.0f, 0, countImage[endCount], TRUE);
            SetDrawMode(DX_DRAWMODE_NEAREST);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }

        if (endCount == 0)
        {
            SetFontSize(200);
            UserInterface::UIText(600, 500, GetColor(255, 255, 255), "Finish!");
        }

        if (fadeState != FADE_NONE)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }

    void Play::GaugeUpdate(float deltaTime)
    {
        gaugeValue -= 1;

        if (gaugeValue < 0)
        {
            gaugeValue = 0;
        }

        if (gaugeValue > gaugeMax)
        {
            gaugeValue = gaugeMax;
        }
    }
}// namespace My3dApp