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

        /** プレイシーンの更新*/
        SceneType Update() override;

        /** プレイシーンの描画*/
        void Draw() override;
    };
}