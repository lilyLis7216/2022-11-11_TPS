#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
    {
        text = "1.Title";

        bgImage = LoadGraph("../asset/image/title.png");
    }

    Title::~Title()
    {
        DeleteGraph(bgImage);
    }

    SceneBase* Title::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(1);

        return retScene;
    }

    void Title::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();
    }
}// namespace My3dApp