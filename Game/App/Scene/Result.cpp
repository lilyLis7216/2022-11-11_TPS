#include "Result.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameManager.h"
#include "../Library/UserInterface.h"
#include "../Library/GamePad.h"
#include "Title.h"

namespace My3dApp
{
    Result::Result()
        : selectState(BACK)
        , nextStar(1000)
    {
        bgImage = LoadGraph("../asset/image/sky.png");

        resultModel = AssetManager::GetMesh("../asset/model/result.mv1");

        MV1SetPosition(resultModel, VGet(0, 350, 0));

        float x = -300.0f;

        backModel = AssetManager::GetMesh("../asset/model/back.mv1");

        MV1SetPosition(backModel, VGet(x, -300, 0));

        MV1SetScale(backModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        exitModel = AssetManager::GetMesh("../asset/model/quit.mv1");

        MV1SetPosition(exitModel, VGet(x, -450, 0));

        MV1SetScale(exitModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        float starY = 100.0f;

        VECTOR starSize = VGet(0.75f, 0.75f, 0.75f);

        string starA = "../asset/model/star1.mv1";

        string starB = "../asset/model/star2.mv1";

        // スコアが1000を超えていたら
        if (GameManager::GetScore() >= 1000)
        {
            // 星を読み込む
            leftStar = AssetManager::GetMesh(starA);
            MV1SetMaterialAmbColor(leftStar, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
            nextStar = 3000;
        }
        // 超えていなかったら
        else
        {
            // 中抜きの星を読み込む
            leftStar = AssetManager::GetMesh(starB);
            MV1SetMaterialAmbColor(leftStar, 0, GetColorF(0.4f, 0.4f, 0.4f, 0.0f));
        }

        // スコアが3000を超えていたら
        if (GameManager::GetScore() >= 3000)
        {
            // 星を読み込む
            rightStar = AssetManager::GetMesh(starA);
            MV1SetMaterialAmbColor(rightStar, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
            nextStar = 5000;
        }
        // 超えていなかったら
        else
        {
            // 中抜きの星を読み込む
            rightStar = AssetManager::GetMesh(starB);
            MV1SetMaterialAmbColor(rightStar, 0, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
        }

        // スコアが5000を超えていたら
        if (GameManager::GetScore() >= 5000)
        {
            // 星を読み込む
            middleStar = AssetManager::GetMesh(starA);
            MV1SetMaterialAmbColor(middleStar, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
            nextStar = 0;
        }
        // 超えていなかったら
        else
        {
            // 中抜きの星を読み込む
            middleStar = AssetManager::GetMesh(starB);
            MV1SetMaterialAmbColor(middleStar, 0, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
        }

        MV1SetScale(middleStar, starSize);
        MV1SetScale(leftStar, starSize);
        MV1SetScale(rightStar, starSize);

        MV1SetPosition(middleStar, VGet(0, starY, 0));
        MV1SetPosition(leftStar, VGet(-300, starY, 0));
        MV1SetPosition(rightStar, VGet(300, starY, 0));

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // 正射影カメラに切り替え
        SetupCamera_Ortho(1000.0f);

        // ライトの方向を設定
        SetLightDirection(VGet(-10.0f, -20.0f, 100.0f));

        SetAlpha(255);

        fadeState = FADE_IN;
    }

    Result::~Result()
    {
        DeleteGraph(bgImage);

        AssetManager::ReleaseMesh(backModel);

        AssetManager::ReleaseMesh(exitModel);

        AssetManager::ReleaseMesh(middleStar);

        AssetManager::ReleaseMesh(rightStar);

        AssetManager::ReleaseMesh(leftStar);
    }

    SceneBase* Result::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(4);

        COLOR_F selectColor = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);

        COLOR_F notSelectColor = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);

        if (fadeState != FADE_OUT)
        {
            if (selectState == BACK)
            {
                MV1SetMaterialAmbColor(backModel, 0, selectColor);
                MV1SetMaterialAmbColor(exitModel, 0, notSelectColor);

                if (GamePad::GetButtonState(Button::B) == 1)
                {
                    AssetManager::PlaySoundEffect("ctrl2", false);
                    nextScene = TITLE;
                    fadeState = FADE_OUT;
                }

                if (GamePad::GetButtonState(Button::DOWN) == 1)
                {
                    AssetManager::PlaySoundEffect("ctrl1", false);
                    selectState = EXIT;
                }
            }
            else if (selectState == EXIT)
            {
                MV1SetMaterialAmbColor(backModel, 0, notSelectColor);
                MV1SetMaterialAmbColor(exitModel, 0, selectColor);

                if (GamePad::GetButtonState(Button::B) == 1)
                {
                    AssetManager::PlaySoundEffect("ctrl2", false);
                    nextScene = QUIT;
                    fadeState = FADE_OUT;
                }

                if (GamePad::GetButtonState(Button::UP) == 1)
                {
                    AssetManager::PlaySoundEffect("ctrl1", false);
                    selectState = BACK;
                }
            }
        }

        if (fadeState == FADE_NONE)
        {
            
        }
        else if (fadeState == FADE_OUT)
        {
            if (alpha <= 255)
            {
                FadeOut();
                if (alpha >= 255)
                {
                    if (nextScene == TITLE)
                    {
                        retScene = new Title();
                    }
                    else if (nextScene == QUIT)
                    {
                        retScene = nullptr;
                    }
                    AssetManager::StopAllSE();
                }
            }
        }
        else if (fadeState == FADE_IN)
        {
            AssetManager::PlaySoundEffect("result", true);
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

    void Result::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        UserInterface::UIBox(320, 1600, 200, 700, 20, GetColor(0, 0, 0), GetColor(0, 0, 255));

        MV1DrawModel(resultModel);

        MV1DrawModel(backModel);

        MV1DrawModel(exitModel);

        MV1DrawModel(middleStar);

        MV1DrawModel(leftStar);

        MV1DrawModel(rightStar);

        SetFontSize(50);

        UserInterface::UIText(450, 600, GetColor(255, 255, 255), "SCORE : %4.0f", (float)GameManager::GetScore());

        if (nextStar > 0)
        {
            UserInterface::UIText(1000, 600, GetColor(255, 255, 255), "NEXT STAR : %4.0f", nextStar - (float)GameManager::GetScore());
        }
        else
        {
            UserInterface::UIText(1000, 600, GetColor(255, 255, 255), "NEXT STAR : %4.0f", 0);
        }

        float sphereY = 0.0f;

        if (selectState == BACK)
        {
            sphereY = -270.0f;
        }
        else if (selectState == EXIT)
        {
            sphereY = -420.0f;
        }

        DrawSphere3D(VGet(-350.0f, sphereY, 0.0f), 20.0f, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

        if (fadeState != FADE_NONE)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }
}// namespace My3dApp