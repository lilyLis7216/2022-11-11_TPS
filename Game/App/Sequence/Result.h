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

        /** リザルトシーンの更新*/
        SceneType Update() override;

        /** リザルトシーンの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/
