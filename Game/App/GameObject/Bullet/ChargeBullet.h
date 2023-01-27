#pragma once

#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// チャージ弾（BaseBullet継承）
    /// </summary>
    class ChargeBullet : public BaseBullet
    {
    private:
        // チャージの状態
        int chargeState;

        bool prevPush;

        bool move;

        bool isCharging = false;   // チャージ中かどうか
 
        float chargeTime = 0;        // チャージ時間

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトの種類</param>
        /// <param name="pos">初期座標</param>
        /// <param name="dir">初期向き</param>
        ChargeBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~ChargeBullet();

        /// <summary>
        /// チャージ弾の更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}