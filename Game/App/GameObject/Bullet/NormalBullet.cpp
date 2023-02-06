#include "NormalBullet.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"
#include "../Effect/HitEffect.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">�I�u�W�F�N�g�̎��</param>
    /// <param name="pos">�������W</param>
    /// <param name="dir">��������</param>
    NormalBullet::NormalBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : BaseBullet(tag, pos, dir)
    {
        // �I�u�W�F�N�g�̎�ނ��v���C���[�e�Ȃ�
        if (tag == ObjectTag::PlayerBullet)
        {
            difColor = GetColor(0, 0, 255);
            boost = 800.0f;
        }
        // �I�u�W�F�N�g�̎�ނ��G�l�~�[�e�Ȃ�
        else if (tag == ObjectTag::EnemyBullet)
        {
            difColor = GetColor(255, 0, 0);
            boost = 1000.0f;
        }

        // �e�̔��a�̐ݒ�
        radius = 25.0f;

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = radius;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    NormalBullet::~NormalBullet()
    {
        // �����Ȃ�
    }

    /// <summary>
    /// �m�[�}���e�̍X�V
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void NormalBullet::Update(float deltaTime)
    {
        if (vanishCount < 0)
        {
            isAlive = false;
        }
        else
        {
            vanishCount -= deltaTime;
        }

        speed = dir * deltaTime * boost;

        pos += speed;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    /// <summary>
    /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
    /// </summary>
    /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
    void NormalBullet::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̎�ނ��擾
        ObjectTag searchTag = other->GetTag();

        // ���g���v���C���[�e�ł����
        if (tag == ObjectTag::PlayerBullet)
        {
            // �G�l�~�[�Ƃ̓����蔻��
            if (searchTag == ObjectTag::Enemy)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }

        // ���g���G�l�~�[�e�ł����
        if (tag == ObjectTag::EnemyBullet)
        {
            // �v���C���[�Ƃ̓����蔻��
            if (searchTag == ObjectTag::Player)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }
    }
}// namespace My3dApp