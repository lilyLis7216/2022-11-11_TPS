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