#include "Title.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"
#include "../Library/GamePad.h"
#include "Explanation.h"
#include "Play.h"

namespace My3dApp
{
    Title::Title()
        : rotateCount(0)
        , selectState(START)
    {
        text = "1.Title";

        titleModel = AssetManager::GetMesh("../asset/model/title.mv1");

        MV1SetPosition(titleModel, VGet(-50.0f, 200.0f, 0));

        MV1SetScale(titleModel, VGet(2.0f, 2.0f, 2.0f));

        MV1SetRotationXYZ(titleModel, VGet(0.0f, 0.0f, 0.0f));

        float x = -200.0f;

        startModel = AssetManager::GetMesh("../asset/model/start.mv1");

        MV1SetPosition(startModel, VGet(x, -150.0f, 0));

        ctrlModel = AssetManager::GetMesh("../asset/model/controls.mv1");

        MV1SetPosition(ctrlModel, VGet(x, -300.0f, 0));

        exitModel = AssetManager::GetMesh("../asset/model/exit.mv1");

        MV1SetPosition(exitModel, VGet(x, -450.0f, 0));

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // 正射影カメラに切り替え
        SetupCamera_Ortho(1000.0f);

        // ライトの方向を設定
        SetLightDirection(VGet(0.0f, 0.0f, 100.0f));
    }

    Title::~Title()
    {
        DeleteGraph(bgImage);

        AssetManager::ReleaseMesh(titleModel);

        AssetManager::ReleaseMesh(startModel);

        AssetManager::ReleaseMesh(ctrlModel);

        AssetManager::ReleaseMesh(exitModel);
    }

    SceneBase* Title::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        MoveModel(deltaTime);

        if (selectState == START)
        {
            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = new Play();
            }

            if (GamePad::GetButtonState(Button::DOWN) == 1 || GamePad::GetLeftStickY() < -10000.0f)
            {
                selectState = CONTROLS;
            }
        }
        else if (selectState == CONTROLS)
        {
            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = new Explanation();
            }

            if (GamePad::GetButtonState(Button::UP) == 1 || GamePad::GetLeftStickY() > 30000.0f)
            {
                selectState = START;
            }

            if (GamePad::GetButtonState(Button::DOWN) == 1 || GamePad::GetLeftStickY() < -30000.0f)
            {
                selectState = EXIT;
            }
        }
        else if (selectState == EXIT)
        {
            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = nullptr;
            }

            if (GamePad::GetButtonState(Button::UP) == 1 || GamePad::GetLeftStickY() > 10000.0f)
            {
                selectState = CONTROLS;
            }
        }

        return retScene;
    }

    void Title::Draw()
    {
        MV1DrawModel(titleModel);

        MV1DrawModel(startModel);

        MV1DrawModel(ctrlModel);

        MV1DrawModel(exitModel);

        float sphereY = 0.0f;

        if (selectState == START)
        {
            sphereY = -120.0f;
        }
        else if (selectState == CONTROLS)
        {
            sphereY = -270.0f;
        }
        else if (selectState == EXIT)

        {
            sphereY = -420.0f;
        }

        DrawSphere3D(VGet(-250.0f, sphereY, 0.0f), 20.0f, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

        CheckNowScene();
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