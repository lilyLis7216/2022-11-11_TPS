#include "Explanation.h"
#include "DxLib.h"

namespace My3dApp
{
    Explanation::Explanation()
    {
        text = "2.explanation";

        bgImage = LoadGraph("../asset/image/explanation.png");
    }

    Explanation::~Explanation()
    {
        DeleteGraph(bgImage);
    }

    SceneBase* Explanation::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(2);

        return retScene;
    }

    void Explanation::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();
    }
}/** namespace My3dApp*/