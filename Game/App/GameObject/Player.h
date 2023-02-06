#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �v���C���[�iGameObject�p���j
    /// </summary>
    class Player : public GameObject
    {
    private:
        // �ڕW����
        VECTOR aimDir;

        // ���x
        VECTOR speed;

        // ��]����
        bool isRotate;

        // �ˌ��̃C���^�[�o��
        float shotInterval;

        // �`���[�W����
        bool isCharge;

        // �m�b�N�o�b�N����
        bool isNockBack;

        // �m�b�N�o�b�N�̌���
        VECTOR knockBackDir;

        float damagePar;

        float knockBackPar;

        const float jumpForce = 200.0f;

        const float GRAVITY = 250.0f;

        float gravity;

        /// <summary>
        /// �v���C���[�̈ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime);

        /// <summary>
        /// �v���C���[�̉�]
        /// </summary>
        void RotateCheck();

        /// <summary>
        /// �ˌ�����
        /// </summary>
        void Shot();

        /// <summary>
        /// �v���C���[�̃m�b�N�o�b�N����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void KnockBack(float deltaTime);

        void DamageParView();

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Player();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Player();

        /// <summary>
        /// �v���C���[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// �v���C���[�̕`��
        /// </summary>
        void Draw() override;

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp