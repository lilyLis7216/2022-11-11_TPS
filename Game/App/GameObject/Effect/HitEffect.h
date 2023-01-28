#pragma once

#include "BaseEffect.h"

namespace My3dApp
{
    /// <summary>
    /// ヒットエフェクト（BaseEffect継承）
    /// </summary>
    class HitEffect : public BaseEffect
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        HitEffect(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~HitEffect();

        /// <summary>        /// ヒットエフェクトの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>

        void Update(float deltaTime) override;
    };
}// namespace My3dApp