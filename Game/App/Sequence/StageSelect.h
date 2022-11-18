#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    class StageSelect : public SceneBase
    {
    public:
        StageSelect();
        ~StageSelect();

        SceneType Update() override;
        void Draw() override;
    };

}/** namespace My3dApp*/