#pragma once
#include "SceneBase.h"

namespace Sequence
{
    /**
    * タイトルクラス
    * シーンベースを継承している
    */
    class Title : public SceneBase
    {
    public:
        Title();
        ~Title();

        SceneType Update() override;
        void Draw() override;
    };

}/** namespace Sequence*/