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
        void Move(float deltaTime)override;

    public:
        void Update(float deltaTime) override;
    };
}// namespace My3dApp