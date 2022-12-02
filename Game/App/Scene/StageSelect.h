#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * ステージセレクトクラス
    * SceneBaseを継承している
    */
    class StageSelect : public SceneBase
    {
    public:
        /** コンストラクタ*/
        StageSelect();

        /** デストラクタ*/
        ~StageSelect();

        /** ステージセレクトの更新*/
        SceneBase* Update(float deltaTime) override;

        /** ステージセレクトの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/