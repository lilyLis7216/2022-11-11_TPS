#pragma once

#include "GameObject.h"
#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// �v���C���[�i�h���N���X�A�p�����F�Q�[���I�u�W�F�N�g�j
    /// </summary>
    class Player : public GameObject
    {
    private:
        // ����
        VECTOR dir;

        // �ڕW����
        VECTOR aimDir;

        // ���x
        VECTOR speed;

        // �A�j���[�V�����Ǘ��p
        class AnimationController* animCtrl;

        // �A�j���[�V������ނ�ID
        int animTypeID;

        // ��]����
        bool isRotate;

        // �v���C���[�̈ړ�
        void Move(float deltaTime);

        // �v���C���[�̉�]
        void RotateCheck();

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