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

        void Shot(float deltaTime) override;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        LightEnemy(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </symmary>
        ~LightEnemy();

        /// <summary>
        /// ���C�g�G�l�~�[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp