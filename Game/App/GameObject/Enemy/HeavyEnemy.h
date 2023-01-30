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
        /// <summary>
        /// �w�r�[�G�l�~�[�̈ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime)override;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        HeavyEnemy(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~HeavyEnemy();

        /// <summary>
        /// �w�r�[�G�l�~�[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp