#pragma once
#include "SceneBase.h"

namespace Sequence
{
    class StageSelect : public SceneBase
    {
    public:
        StageSelect();
        ~StageSelect();

        SceneType Update() override;
        void Draw() override;
    };

}/** namespace Sequence*/