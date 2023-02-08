#include "Title.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    Title::Title()
    {
        text = "1.Title";

        bgImage = LoadGraph("../asset/image/title.pn");

        titleModel = AssetManager::GetMesh("../asset/model/title.mv1");

        MV1SetPosition(titleModel, VGet(0, 0, 0));

        MV1SetRotationXYZ(titleModel, VGet(0.75f, 0.0f, 0.0f));

        // カメラの位置と向きを設定
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        // ライトの方向を設定
        SetLightDirection(VGet(0.0f, 0.0f, 100.0f));
    }

    Title::~Title()
    {
        DeleteGraph(bgImage);

        AssetManager::ReleaseMesh(titleModel);
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

        CheckNowScene();
    }

    void Title::MoveModel(float deltaTime)
    {
        rotateCount += deltaTime;

        /*if (rotateCount < 12.0f)
        {
            rotateCount = 0.0f;
        }*/

        MV1SetRotationXYZ(titleModel, VGet(0.0f, rotateCount, 0.0f));
    }
}// namespace My3dApp