#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
        : SceneBase(SceneType::Scene_Title)
    {
        text = "1.Title";
    }

    Title::~Title()
    {
        /** �����Ȃ�*/
    }

    SceneType Title::Update()
    {
        nowSceneType = SceneType::Scene_Title;

        InputCheck();

        return nowSceneType;
    }

    void Title::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/