#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">�I�u�W�F�N�g�̎��</param>
    BaseBullet::BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag, pos)
        , dir(dir)
        , speed(VGet(0, 0, 0))
        , vanishCount(5.0f)
        , boost(0)
        , bulletType(-1)
    {
        // �����蔻���ނ̐ݒ�
        collisionType = CollisionType::Sphere;

        // �����蔻�苅�̃��[�J�����W�̏�����
        collisionSphere.localCenter = VGet(0, 0, 0);

        // �����蔻�苅�̃��[���h���W�̏�����
        collisionSphere.worldCenter = this->pos;
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    BaseBullet::~BaseBullet()
    {
        // �����Ȃ�
    }

    /// <summary>
    /// �e�̕`��
    /// </summary>
    void BaseBullet::Draw()
    {
        // ���f���̕`��
        MV1DrawModel(modelHandle);

        // �����蔻��̕`��(�K�v�ȏꍇ��R�����g��)
        //DrawCollider();
    }
}// namespace My3dApp