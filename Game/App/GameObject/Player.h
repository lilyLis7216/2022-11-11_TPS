#pragma once

#include "GameObject.h"
#include <DxLib.h>

namespace My3dApp
{
    class Player : public GameObject
    {
    private:
        /** 向き*/
        VECTOR dir;

        /** 目標向き*/
        VECTOR aimDir;

        /** 速度*/
        VECTOR speed;

        /** スティックのx座標*/
        int stickX;

        /** スティックのy座標*/
        int stickY;

        /** 入力確認*/
        void InputCheck();

        /** 移動*/
        void Move();

    public:
        /** コンストラクタ*/
        Player();

        /** デストラクタ*/
        ~Player();

        /** プレイヤーの更新*/
        void Update(float deltaTime) override;

        /** プレイヤーの描画*/
        void Draw() override;
    };

}/** namespace My3dApp*/