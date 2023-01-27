#pragma once

#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// ノーマル弾クラス（BaseBullet継承）
    /// </summary>
    class NormalBullet : public BaseBullet
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトの種類</param>
        /// <param name="pos">初期座標</param>
        /// <param name="dir">初期向き</param>
        NormalBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~NormalBullet();

        /// <summary>
        /// ノーマル弾の更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp