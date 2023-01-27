#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Bullet : public GameObject
    {
    private:
        VECTOR speed;

        VECTOR dir;

        float boost;

        float deadCount;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="setTag">�I�u�W�F�N�g�̃^�O</param>
        /// <param name="initPos">�����ʒu</param>
        /// <param name="initDir">����</param>
        Bullet(ObjectTag setTag, VECTOR initPos, VECTOR initDir);

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