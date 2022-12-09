#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /**
    * タイトルクラス
    * SceneBaseを継承している
    */
    class Title : public SceneBase
    {
    public:
        /** コンストラクタ*/
        Title();

        /** デストラクタ*/
        ~Title();

        /** タイトルの更新*/
        SceneBase* Update(float deltaTime) override;

        /** タイトルの描画*/
        void Draw() override;
    };
}/** namespace My3dApp*/