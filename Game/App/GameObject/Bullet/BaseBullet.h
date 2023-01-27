#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// 弾の基底クラス（GameObject継承）
    /// </summary>
    class BaseBullet : public GameObject
    {
    protected:
        // 向き
        VECTOR dir;

        // 速度
        VECTOR speed;

        // 消失までのカウント
        float vanishCount;

        // 消失カウントの初期値
        float const initVanishCount = 5.0f;

        // 弾にかける加速
        float boost;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトの種類</param>
        BaseBullet(ObjectTag tag);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~BaseBullet();

        // 弾の種類
        enum BulletType
        {
            Normal = 0,  // ノーマル弾
            Charge,      // チャージ弾
        };
    };
}// namespace My3dApp