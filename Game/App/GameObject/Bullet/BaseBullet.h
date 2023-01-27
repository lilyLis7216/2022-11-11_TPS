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
        // ����
        VECTOR dir;

        // ���x
        VECTOR speed;

        // �����܂ł̃J�E���g
        float vanishCount;

        // �����J�E���g�̏����l
        float const initVanishCount = 5.0f;

        // �e�ɂ��������
        float boost;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̎��</param>
        BaseBullet(ObjectTag tag);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~BaseBullet();

        // �e�̎��
        enum BulletType
        {
            Normal = 0,  // �m�[�}���e
            Charge,      // �`���[�W�e
        };
    };
}// namespace My3dApp