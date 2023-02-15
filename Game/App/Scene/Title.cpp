#include "Title.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameManager.h"
#include "../Library/GamePad.h"
#include "Explanation.h"
#include "Play.h"

namespace My3dApp
{
    Title::Title()
        : rotateCount(0)
        , selectState(START)
    {
        titleModel = AssetManager::GetMesh("../asset/model/title.mv1");

        MV1SetPosition(titleModel, VGet(-50.0f, 200.0f, 0));

        MV1SetScale(titleModel, VGet(2.0f, 2.0f, 2.0f));

        MV1SetRotationXYZ(titleModel, VGet(0.0f, 0.0f, 0.0f));

        float x = -200.0f;

        startModel = AssetManager::GetMesh("../asset/model/start.mv1");

        MV1SetPosition(startModel, VGet(x, -200.0f, 0));

        MV1SetScale(startModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        exitModel = AssetManager::GetMesh("../asset/model/quit.mv1");

        MV1SetPosition(exitModel, VGet(x, -350.0f, 0));

        MV1SetScale(exitModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        movie = LoadGraph("../asset/image/titleVideo.mp4");

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // 正射影カメラに切り替え
        SetupCamera_Ortho(1000.0f);

        // ライトの方向を設定
        SetLightDirection(VGet(0.0f, 0.0f, 100.0f));

        GameManager::ResetScore();

        SetAlpha(255);

        fadeState = FADE_IN;
    }

    Title::~Title()
    {
        PauseMovieToGraph(movie);

        DeleteGraph(movie);

        AssetManager::ReleaseMesh(titleModel);

        AssetManager::ReleaseMesh(startModel);

        AssetManager::ReleaseMesh(exitModel);
    }

    SceneBase* Title::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        AssetManager::PlaySoundEffect("title", true);

        if (!GetMovieStateToGraph(movie))
        {
            PauseMovieToGraph(movie);
            SeekMovieToGraph(movie, 0);
            PlayMovieToGraph(movie);
        }

        retScene = CheckRetScene(1);

        COLOR_F selectColor = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);

        COLOR_F notSelectColor = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);

        if (fadeState != FADE_OUT)
        {
            if (selectState == START)
            {
                MV1SetMaterialAmbColor(startModel, 0, selectColor);
                MV1SetMaterialAmbColor(exitModel, 0, notSelectColor);

                if (GamePad::GetButtonState(Button::B) == 1)
                {
                    AssetManager::PlaySoundEffect("ctrl2", false);
                    nextScene = PLAY;
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
                MV1SetMaterialAmbColor(startModel, 0, notSelectColor);
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
                    selectState = START;
                }
            }
        }

        if (fadeState == FADE_NONE)
        {
            MoveModel(deltaTime);
        }
        else if (fadeState == FADE_OUT)
        {
            MoveModel(deltaTime);
            FadeOut();
            if (alpha >= 255)
            {
                if (nextScene == PLAY)
                {
                    retScene = new Play();
                }
                else if (nextScene == QUIT)
                {
                    retScene = nullptr;
                }
                AssetManager::StopAllSE();
            }
        }
        else if (fadeState == FADE_IN)
        {
            FadeIn();
            if (alpha <= 0)
            {
                fadeState = FADE_NONE;
            }
        }

        return retScene;
    }

    void Title::Draw()
    {
        DrawRotaGraph(960, 540, 1.5f, 0, movie, FALSE);

        MV1DrawModel(titleModel);

        MV1DrawModel(startModel);

        MV1DrawModel(exitModel);

        float sphereY = 0.0f;

        if (selectState == START)
        {
            sphereY = -170.0f;
        }
        else if (selectState == EXIT)

        {
            sphereY = -320.0f;
        }

        DrawSphere3D(VGet(-250.0f, sphereY, 0.0f), 20.0f, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

        if (fadeState != FADE_NONE)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }

    void Title::MoveModel(float deltaTime)
    {
        rotateCount += deltaTime;

        if (rotateCount > 1.6f)
        {
            rotateCount = -1.5f;
        }

        MV1SetRotationXYZ(titleModel, VGet(0.0f, rotateCount, 0.0f));
    }
}// namespace My3dApp