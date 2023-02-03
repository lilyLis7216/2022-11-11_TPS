#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �G�l�~�[�̊��N���X�iGameObject�p���j
    /// </summary>
    class BaseEnemy : public GameObject
    {
    protected:
        // ����
        VECTOR dir;

        // �ڕW����
        VECTOR aimDir;

        // ���x
        VECTOR speed;

        // ��]����
        bool isRotate;

        // ���˂̊Ԋu
        float shotInterval;

        // �~�σ_���[�W
        float damagePar;

        // �m�b�N�o�b�N����
        bool isNockBack;

        // �m�b�N�o�b�N�̌���
        VECTOR nockBackDir;

        const float jumpForce = 200.0f;

        float weight;

        float nockBackPar;

        float gravity;

        /// <summary>
        /// �G�l�~�[�̈ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        virtual void Move(float deltaTime) = 0;

        /// <summary>
        /// ��]�̊m�F
        /// </summary>
        void RotateCheck();

        /// <summary>
        /// �~�σ_���[�W�̕\��
        /// </summary>
        void DamageParView();

        /// <summary>
        /// ����ł��邩�ǂ����̊m�F
        /// </summary>
        /// <returns>true ����ł��� false ����ł��Ȃ�</returns>
        bool IsDead();

        void Shot();

        /// <summary>
        /// �G�l�~�[�̃m�b�N�o�b�N����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        virtual void KnockBack(float deltaTime) = 0;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        BaseEnemy(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~BaseEnemy();

        /// <summary>
        /// �G�l�~�[�̕`��
        /// </summary>
        void Draw() override;

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}