#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Map : public GameObject
    {
    public:
        /** コンストラクタ*/
        Map();

        /** コンストラクタ（座標指定）*/
        Map(VECTOR pos);

        /** デストラクタ*/
        ~Map();

        /** モデルの読み込み*/
        void ModelLoad();

        /** 更新*/
        void Update(float deltaTime) override;

        /** 描画*/
        void Draw() override;
    };
}/** namespace My3dApp*/