#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">�I�u�W�F�N�g�̎��</param>
    BaseBullet::BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag, pos)
        , speed(VGet(0, 0, 0))
        , bulletType(-1)
        , radius(0)
        , divNum(16)
        , difColor(-1)
        , spcColor(-1)
        , isFill(true)
        , vanishCount(5.0f)
        , boost(0)
    {
        // ������ݒ�
        this->dir = dir;

        // �����蔻���ނ̐ݒ�
        collisionType = CollisionType::Sphere;

        // �����蔻�苅�̃��[�J�����W�̏�����
        collisionSphere.localCenter = VGet(0, 0, 0);
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
        // ���̕`��
        DrawSphere3D(pos, collisionSphere.radius, divNum, difColor, spcColor, isFill);

        // �����蔻��̕`��
        DrawCollider();
    }
}// namespace My3dApp