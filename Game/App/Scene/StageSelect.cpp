#include "StageSelect.h"
#include "DxLib.h"

namespace My3dApp
{
    StageSelect::StageSelect()
    {
        text = "2.StageSelect";
    }

    StageSelect::~StageSelect()
    {
    }

    SceneBase* StageSelect::Update()
    {
        ChangeScene();
        /** âΩÇ‡Ç»ÇØÇÍÇŒé©êgÇï‘Ç∑*/
        return this;
    }

    void StageSelect::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/