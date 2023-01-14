#include "Result.h"
#include "DxLib.h"

namespace My3dApp
{
    Result::Result()
    {
        text = "4.Result";

        bgImage = LoadGraph("../asset/image/result.png");
    }

    Result::~Result()
    {
        DeleteGraph(bgImage);
    }

    SceneBase* Result::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(4);

        return retScene;
    }

    void Result::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();
    }
}// namespace My3dApp