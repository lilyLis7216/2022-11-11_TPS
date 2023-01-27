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

        float shotInterval;

        float damagePar;

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

        void Shot();

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