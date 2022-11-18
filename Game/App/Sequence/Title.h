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

        /** タイトルシーンの更新*/
        SceneType Update() override;

        /** タイトルシーンの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/