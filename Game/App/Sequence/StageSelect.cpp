#include "StageSelect.h"
#include "DxLib.h"

namespace My3dApp
{
    StageSelect::StageSelect()
        : SceneBase(SceneType::Scene_StageSelect)
    {
        text = "2.StageSelect";
    }

    StageSelect::~StageSelect()
    {
    }

    SceneType StageSelect::Update()
    {
        nowSceneType = SceneType::Scene_StageSelect;

        InputCheck();

        return nowSceneType;
    }

    void StageSelect::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/