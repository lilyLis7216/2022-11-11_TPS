#pragma once

#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �m�[�}���e�N���X�iBaseBullet�p���j
    /// </summary>
    class NormalBullet : public BaseBullet
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̎��</param>
        /// <param name="pos">�������W</param>
        /// <param name="dir">��������</param>
        NormalBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~NormalBullet();

        /// <summary>
        /// �m�[�}���e�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp