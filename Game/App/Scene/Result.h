#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * リザルトクラス
    * SceneBaseを継承している
    */
    class Result : public SceneBase
    {
    public:
        /** コンストラクタ*/
        Result();

        /** デストラクタ*/
        ~Result();

        /** リザルトの更新*/
        SceneBase* Update() override;

        /** リザルトの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/