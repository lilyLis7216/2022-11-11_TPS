#include "Explanation.h"
#include "DxLib.h"
#include "../Library/GamePad.h"
#include "Title.h"

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

        if (GamePad::GetButtonState(Button::BACK) == 1)
        {
            retScene = new Title();
        }

        return retScene;
    }

    void Explanation::Draw()
    {
        DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();
    }
}/** namespace My3dApp*/