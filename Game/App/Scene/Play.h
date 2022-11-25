#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * プレイクラス
    * SceneBaseを継承している
    */
    class Play : public SceneBase
    {
    public:
        /** コンストラクタ*/
        Play();

        /** デストラクタ*/
        ~Play();

        /** プレイの更新*/
        SceneBase* Update() override;

        /** プレイの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/