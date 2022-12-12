#pragma once

#include "GameObject.h"
#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// プレイヤー（派生クラス、継承元：ゲームオブジェクト）
    /// </summary>
    class Player : public GameObject
    {
    private:
        // 向き
        VECTOR dir;

        // 目標向き
        VECTOR aimDir;

        // 速度
        VECTOR speed;

        // アニメーション管理用
        class AnimationController* animCtrl;

        // アニメーション種類のID
        int animTypeID;

        // 回転中か
        bool isRotate;

        // プレイヤーの移動
        void Move(float deltaTime);

        // プレイヤーの回転
        void RotateCheck();

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Player();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Player();

        /// <summary>
        /// プレイヤーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// プレイヤーの描画
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;

    };
}// namespace My3dApp