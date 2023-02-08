#include "Title.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    Title::Title()
        : rotateCount(0)
        , selectState(0)
    {
        text = "1.Title";

        bgImage = LoadGraph("../asset/image/title.pn");

        titleModel = AssetManager::GetMesh("../asset/model/title.mv1");

        MV1SetPosition(titleModel, VGet(0, 0, 0));

        MV1SetRotationXYZ(titleModel, VGet(0.75f, 0.0f, 0.0f));

        MV1SetScale(titleModel, VGet(1.0f, 1.0f, 1.0f));

        startModel = AssetManager::GetMesh("../asset/model/start.mv1");

        MV1SetPosition(startModel, VGet(0, -250.0f, 0));

        MV1SetScale(startModel, VGet(1.0f, 1.0f, 1.0f));

        MV1SetRotationXYZ(startModel, VGet(0.1f, 0, 0));

        exitModel = AssetManager::GetMesh("../asset/model/exit.mv1");

        MV1SetPosition(exitModel, VGet(0, -400.0f, 0));

        MV1SetScale(exitModel, VGet(1.0f, 1.0f, 1.0f));

        MV1SetRotationXYZ(exitModel, VGet(0.3f, 0, 0));

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // ライトの方向を設定
        SetLightDirection(VGet(0.0f, 0.0f, 100.0f));
    }

    Title::~Title()
    {
        DeleteGraph(bgImage);

        AssetManager::ReleaseMesh(titleModel);

        AssetManager::ReleaseMesh(startModel);

        AssetManager::ReleaseMesh(exitModel);
    }

    SceneBase* Title::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        MoveModel(deltaTime);

        retScene = CheckRetScene(1);

        return retScene;
    }

    void Title::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        MV1DrawModel(titleModel);

        MV1DrawModel(startModel);

        MV1DrawModel(exitModel);

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