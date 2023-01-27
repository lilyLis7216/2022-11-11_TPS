#pragma once

#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �`���[�W�e�iBaseBullet�p���j
    /// </summary>
    class ChargeBullet : public BaseBullet
    {
    private:
        // �`���[�W�̏��
        int chargeState;

        bool prevPush;

        bool move;

        bool isCharging = false;   // �`���[�W�����ǂ���
 
        float chargeTime = 0;        // �`���[�W����

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̎��</param>
        /// <param name="pos">�������W</param>
        /// <param name="dir">��������</param>
        ChargeBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~ChargeBullet();

        /// <summary>
        /// �`���[�W�e�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}