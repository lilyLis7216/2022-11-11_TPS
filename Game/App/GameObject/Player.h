#pragma once

#include "GameObject.h"
#include "DxLib.h"

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

        /** アニメーション管理用*/
        class AnimationController* animCtrl;

        /** アニメーションの種類ID*/
        int animTypeID;

        /** 回転中か*/
        bool isRotate;

        /** パッドの入力状態*/
        int padInputState;

        /** スティックのx座標*/
        int stickX;

        /** スティックのy座標*/
        int stickY;

        /** 移動*/
        void Move(float deltaTime);

        /** 回転*/
        void RotateCheck();

    public:
        /** コンストラクタ*/
        Player();

        /** デストラクタ*/
        ~Player();

        /** プレイヤーの更新*/
        void Update(float deltaTime) override;

        /** プレイヤーの描画*/
        void Draw() override;

        /** 当たり判定*/
        void OnCollisionEnter(const GameObject* other) override;
    };
}/** namespace My3dApp*/