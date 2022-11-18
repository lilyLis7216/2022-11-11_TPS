#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
        : SceneBase(SceneType::Scene_Title)
    {
        /** ˆ—‚È‚µ*/
    }

    Title::~Title()
    {
        /** ˆ—‚È‚µ*/
    }

    SceneType Title::Update()
    {
        nowSceneType = SceneType::Scene_Title;

        if (CheckHitKey(KEY_INPUT_Z))
        {
            nowSceneType = SceneType::Scene_StageSelect;
        }

        return nowSceneType;
    }

    void Title::Draw()
    {
        DrawFormatString(100, 200, GetColor(255, 255, 255), "ƒ^ƒCƒgƒ‹");
    }
}/** namespace My3dApp*/