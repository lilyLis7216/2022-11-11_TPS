#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// ���C�g�G�l�~�[�N���X�iBaseEnemy�p���j
    /// </summary>
    class LightEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// ���C�g�G�l�~�[�̈ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime)override;

    public:
        LightEnemy(VECTOR pos);
        ~LightEnemy();

        /// <summary>
        /// ���C�g�G�l�~�[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp