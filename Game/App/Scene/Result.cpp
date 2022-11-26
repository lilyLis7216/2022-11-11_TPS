#include "Result.h"
#include "DxLib.h"

namespace My3dApp
{
    Result::Result()
    {
        text = "4.Result";
    }

    Result::~Result()
    {
    }

    SceneBase* Result::Update()
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(4);

        return retScene;
    }

    void Result::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/