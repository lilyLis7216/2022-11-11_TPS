#include "StageSelect.h"
#include "DxLib.h"

namespace My3dApp
{
    StageSelect::StageSelect()
    {
        text = "2.explanation";

        bgImage = LoadGraph("../asset/image/explanation.png");
    }

    StageSelect::~StageSelect()
    {
        DeleteGraph(bgImage);
    }

    SceneBase* StageSelect::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(2);

        return retScene;
    }

    void StageSelect::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();
    }
}/** namespace My3dApp*/