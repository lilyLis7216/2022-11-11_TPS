#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// プレイヤー（GameObject継承）
    /// </summary>
    class Player : public GameObject
    {
    private:
        // 目標向き
        VECTOR aimDir;

        // 速度
        VECTOR speed;

        // 回転中か
        bool isRotate;

        // 射撃のインターバル
        float shotInterval;

        // チャージ中か
        bool isCharge;

        // ノックバック中か
        bool isNockBack;

        // ノックバックの向き
        VECTOR knockBackDir;

        float damagePar;

        float knockBackPar;

        const float jumpForce = 200.0f;

        const float GRAVITY = 250.0f;

        float gravity;

        /// <summary>
        /// プレイヤーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime);

        /// <summary>
        /// プレイヤーの回転
        /// </summary>
        void RotateCheck();

        /// <summary>
        /// 射撃処理
        /// </summary>
        void Shot();

        /// <summary>
        /// プレイヤーのノックバック処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void KnockBack(float deltaTime);

        void DamageParView();

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