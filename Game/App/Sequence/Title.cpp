#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
        : SceneBase(SceneType::Scene_Title)
    {
        /** �����Ȃ�*/
    }

    Title::~Title()
    {
        /** �����Ȃ�*/
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
        DrawFormatString(100, 200, GetColor(255, 255, 255), "�^�C�g��");
    }
}/** namespace My3dApp*/