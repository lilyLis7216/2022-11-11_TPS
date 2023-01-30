#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// ヘビーエネミークラス（BaseEnemy継承）
    /// </summary>
    class HeavyEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// ヘビーエネミーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime)override;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        HeavyEnemy(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~HeavyEnemy();

        /// <summary>
        /// ヘビーエネミーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp