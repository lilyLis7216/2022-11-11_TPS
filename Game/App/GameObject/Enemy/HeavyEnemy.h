#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// �w�r�[�G�l�~�[�N���X�iBaseEnemy�p���j
    /// </summary>
    class HeavyEnemy : public BaseEnemy
    {
    private:
        void Move(float deltaTime)override;

    public:
        void Update(float deltaTime) override;
    };
}// namespace My3dApp