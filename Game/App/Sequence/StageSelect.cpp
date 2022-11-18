#include "StageSelect.h"
#include "DxLib.h"

namespace My3dApp
{
    StageSelect::StageSelect()
        : SceneBase(SceneType::Scene_StageSelect)
    {
    }
    StageSelect::~StageSelect()
    {
    }
    SceneType StageSelect::Update()
    {
        nowSceneType = SceneType::Scene_StageSelect;

        if (CheckHitKey(KEY_INPUT_X))
        {
            nowSceneType = SceneType::Scene_Title;
        }

        return nowSceneType;
    }
    void StageSelect::Draw()
    {
        DrawFormatString(100, 200, GetColor(255, 255, 255), "ステージセレクト");
    }
}/** namespace My3dApp*/