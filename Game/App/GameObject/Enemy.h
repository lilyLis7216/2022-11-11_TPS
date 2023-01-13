#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// エネミー（派生クラス、継承元：ゲームオブジェクト）
    /// </summary>
    class Enemy : public GameObject
    {
    private:
        // 向き
        VECTOR dir;

        // 目標向き
        VECTOR aimDir;

        // 速度
        VECTOR speed;

        // アニメーション種類のID
        int animTypeID;

        // 回転中か
        bool isRotate;

        float moveCount;

        float isMove;

        int moveTmp;

        void Move(float deltaTime);

        void RotateCheck();

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Enemy();

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        Enemy(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Enemy();

        /// <summary>
        /// エネミーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// エネミーの描画
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp