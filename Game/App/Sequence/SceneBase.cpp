#include "SceneBase.h"
#include "DxLib.h"

namespace My3dApp
{
    SceneBase::SceneBase(SceneType sceneType)
        : nowSceneType(sceneType)
        , text(nullptr)
    {
        /** èàóùÇ»Çµ*/
    }

    SceneBase::~SceneBase()
    {
        /** èàóùÇ»Çµ*/
    }

    void SceneBase::CheckNowScene()
    {
        DrawFormatString(100, 200, GetColor(255, 255, 255), "%s", text);
    }

    void SceneBase::InputCheck()
    {
        if (CheckHitKey(KEY_INPUT_1))
        {
            nowSceneType = SceneType::Scene_Title;
        }

        if (CheckHitKey(KEY_INPUT_2))
        {
            nowSceneType = SceneType::Scene_StageSelect;
        }

        if (CheckHitKey(KEY_INPUT_3))
        {
            nowSceneType = SceneType::Scene_Play;
        }

        if (CheckHitKey(KEY_INPUT_4))
        {
            nowSceneType = SceneType::Scene_Result;
        }
    }

}/** namespace My3dApp*/