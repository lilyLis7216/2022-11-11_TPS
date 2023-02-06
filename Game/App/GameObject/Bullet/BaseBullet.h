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
        // 速度
        VECTOR speed;

        // 弾の半径
        float radius;

        // 形成時のポリゴンの細かさ
        int divNum;

        // ディフューズカラー
        int difColor;

        // スペキュラカラー
        int spcColor;

        // 塗りつぶし
        bool isFill;

        // 消失までのカウント
        float vanishCount;

        // 弾にかける加速
        float boost;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトの種類</param>
        BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~BaseBullet();

        /// <summary>
        /// 弾の描画
        /// </summary>
        void Draw() override;

        // 弾の種類
        enum BulletType
        {
            Normal = 0,  // ノーマル弾
            Charge,      // チャージ弾
        };
    };
}// namespace My3dApp