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
        ChangeScene();
        /** âΩÇ‡Ç»ÇØÇÍÇŒé©êgÇï‘Ç∑*/
        return this;
    }

    void Result::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/