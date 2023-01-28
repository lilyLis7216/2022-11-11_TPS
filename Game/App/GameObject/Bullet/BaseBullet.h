#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �e�̊��N���X�iGameObject�p���j
    /// </summary>
    class BaseBullet : public GameObject
    {
    protected:
        // ���x
        VECTOR speed;

        // �����܂ł̃J�E���g
        float vanishCount;

        // �e�ɂ��������
        float boost;

        // �e�̎��
        int bulletType;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̎��</param>
        BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~BaseBullet();

        /// <summary>
        /// �e�̕`��
        /// </summary>
        void Draw() override;

        // �e�̎��
        enum BulletType
        {
            Normal = 0,  // �m�[�}���e
            Charge,      // �`���[�W�e
        };
    };
}// namespace My3dApp