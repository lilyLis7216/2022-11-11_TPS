#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
    {
        text = "1.Title";
    }

    Title::~Title()
    {
        /** èàóùÇ»Çµ*/
    }

    SceneBase* Title::Update()
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(1);

        return retScene;
    }

    void Title::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/