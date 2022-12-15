#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Bullet : public GameObject
    {
    private:
        VECTOR speed;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̃^�O</param>
        Bullet(ObjectTag tag);

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̃^�O</param>
        /// <param name="pos">�����ʒu</param>
        Bullet(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary<
        ~Bullet();

        /// <summary>
        /// �e�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// �e�̕`��
        /// </summary>
        void Draw() override;

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp