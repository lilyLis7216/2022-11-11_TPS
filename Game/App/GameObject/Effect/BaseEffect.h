#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// エフェクトの基底クラス（GameObject継承）
    /// </summary>
    class BaseEffect : public GameObject
    {
    protected:
        // エフェクトハンドル
        int effectHandle;

        // 再生するエフェクト
        int playEffect;

        // 再生中か
        bool isPlay;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        BaseEffect(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~BaseEffect();

        /// <summary>
        /// エフェクトの描画
        /// </summary>
        void Draw() override;
    };
}// namespace My3dApp