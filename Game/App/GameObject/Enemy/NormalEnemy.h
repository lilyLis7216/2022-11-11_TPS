#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// �m�[�}���G�l�~�[�N���X�iBaseEnemy�p���j
    /// </summary>
    class NormalEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// �m�[�}���G�l�~�[�̈ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime) override;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos"></param>
        NormalEnemy( VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~NormalEnemy();
        
        /// <summary>
        /// �m�[�}���G�l�~�[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp