#pragma once
#include "SceneBase.h"

namespace My3dApp
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

}/** namespace My3dApp*/