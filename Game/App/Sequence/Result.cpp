#include "Result.h"
#include "DxLib.h"

namespace My3dApp
{
    Result::Result()
        :SceneBase(SceneType::Scene_Result)
    {
        text = "4.Result";
    }

    Result::~Result()
    {
    }

    SceneType Result::Update()
    {
        nowSceneType = SceneType::Scene_Result;

        InputCheck();

        return nowSceneType;
    }

    void Result::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/