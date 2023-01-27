#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// ライトエネミークラス（BaseEnemy継承）
    /// </summary>
    class LightEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// ライトエネミーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime)override;

    public:
        LightEnemy(VECTOR pos);
        ~LightEnemy();

        /// <summary>
        /// ライトエネミーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp