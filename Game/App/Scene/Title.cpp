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

        MV1SetPosition(startModel, VGet(x, -150.0f, 0));

        MV1SetScale(startModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        ctrlModel = AssetManager::GetMesh("../asset/model/controls.mv1");

        MV1SetPosition(ctrlModel, VGet(x, -300.0f, 0));

        MV1SetScale(ctrlModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        exitModel = AssetManager::GetMesh("../asset/model/quit.mv1");

        MV1SetPosition(exitModel, VGet(x, -450.0f, 0));

        MV1SetScale(exitModel, VGet(notSelectSize, notSelectSize, notSelectSize));

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // 正射影カメラに切り替え
        SetupCamera_Ortho(1000.0f);

        // ライトの方向を設定
        SetLightDirection(VGet(0.0f, 0.0f, 100.0f));

        GameManager::ResetScore();
    }

    Title::~Title()
    {
        AssetManager::ReleaseMesh(titleModel);

        AssetManager::ReleaseMesh(startModel);

        AssetManager::ReleaseMesh(ctrlModel);

        AssetManager::ReleaseMesh(exitModel);
    }

    SceneBase* Title::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        MoveModel(deltaTime);

        retScene = CheckRetScene(1);

        COLOR_F selectColor = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);

        COLOR_F notSelectColor = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);

        if (selectState == START)
        {
            MV1SetMaterialAmbColor(startModel, 0, selectColor);
            MV1SetMaterialAmbColor(ctrlModel, 0, notSelectColor);
            MV1SetMaterialAmbColor(exitModel, 0, notSelectColor);

            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = new Play();
            }

            if (GamePad::GetButtonState(Button::DOWN) == 1)
            {
                selectState = CONTROLS;
            }
        }
        else if (selectState == CONTROLS)
        {
            MV1SetMaterialAmbColor(startModel, 0, notSelectColor);
            MV1SetMaterialAmbColor(ctrlModel, 0, selectColor);
            MV1SetMaterialAmbColor(exitModel, 0, notSelectColor);

            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = new Explanation();
            }

            if (GamePad::GetButtonState(Button::UP) == 1)
            {
                selectState = START;
            }

            if (GamePad::GetButtonState(Button::DOWN) == 1)
            {
                selectState = EXIT;
            }
        }
        else if (selectState == EXIT)
        {
            MV1SetMaterialAmbColor(startModel, 0, notSelectColor);
            MV1SetMaterialAmbColor(ctrlModel, 0, notSelectColor);
            MV1SetMaterialAmbColor(exitModel, 0, selectColor);

            if (GamePad::GetButtonState(Button::B) == 1)
            {
                retScene = nullptr;
            }

            if (GamePad::GetButtonState(Button::UP) == 1)
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