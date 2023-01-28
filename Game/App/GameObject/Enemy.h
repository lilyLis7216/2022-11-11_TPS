#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �G�l�~�[�iGameObject�p���j
    /// </summary>
    class Enemy : public GameObject
    {
    private:
        // �ڕW����
        VECTOR aimDir;

        // ���x
        VECTOR speed;

        // �A�j���[�V������ނ�ID
        int animTypeID;

        // ��]����
        bool isRotate;

        float shotInterval;

        float nockBackPar;

        void Move(float deltaTime);

        void RotateCheck();

        void Shot();

        void NockBackParView();

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Enemy();

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        Enemy(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Enemy();

        /// <summary>
        /// �G�l�~�[�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

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
}// namespace My3dApp