#pragma once

#include "BaseEffect.h"

namespace My3dApp
{
    /// <summary>
    /// �q�b�g�G�t�F�N�g�iBaseEffect�p���j
    /// </summary>
    class HitEffect : public BaseEffect
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        HitEffect(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~HitEffect();

        /// <summary>        /// �q�b�g�G�t�F�N�g�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>

        void Update(float deltaTime) override;
    };
}// namespace My3dApp