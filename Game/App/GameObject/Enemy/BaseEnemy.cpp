#include "BaseEnemy.h"
#include "../../Manager/EnemyManager.h"
#include "../../Library/Calc3D.h"
#include "../../Manager/GameObjectManager.h"
#include "../Bullet/NormalBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�����ʒu</param>
    BaseEnemy::BaseEnemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , dir(VGet(1, 0, 0))
        , aimDir(dir)
        , speed(VGet(0, 0, 0))
        , isRotate(false)
        , shotInterval(2.0f)
        , damagePar(0.0f)
    {
        // �����蔻���ނ̐ݒ�
        collisionType = CollisionType::Sphere;

        // ���̃��[�J�����S���W�̏�����
        collisionSphere.localCenter = VGet(0, 0, 0);

        // ���`�����蔻��̒ǉ�
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // �G�l�~�[�̌��ݐ��𑝂₷
        EnemyManager::AddNum();
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    BaseEnemy::~BaseEnemy()
    {
        // �G�l�~�[�̌��ݐ������炷
        EnemyManager::SubNum();
    }

    /// <summary>
    /// �G�l�~�[�̕`��
    /// </summary>
    void BaseEnemy::Draw()
    {
        // ���f���̕`��
        MV1DrawModel(modelHandle);

        // �����蔻��̕`��
        //DrawCollider();

        // �~�σ_���[�W�̕\��
        DamageParView();
    }

    /// <summary>
    /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
    /// </summary>
    /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
    void BaseEnemy::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̃^�O���擾
        ObjectTag tag = other->GetTag();

        // �}�b�v�Ƃ̏Փ�
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // �}�b�v�Ǝ��g�̋��E���Ƃ̓����蔻��
            MV1_COLL_RESULT_POLY_DIM collInfo;

            // �������Ă���ꍇ
            if (CollisionPair(collisionSphere, collModel, collInfo))
            {
                // �����߂���
                VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(collisionSphere, collInfo);

                // �����߂�
                pos += pushBackVec;

                onGround = true;

                // �����蔻����̉��
                MV1CollResultPolyDimTerminate(collInfo);

                // �����蔻��̍X�V
                CollisionUpdate();
            }
            else
            {
                onGround = false;

                CollisionUpdate();
            }

            // �w�i�Ƒ������������蔻��
            MV1_COLL_RESULT_POLY collInfoLine;

            // �������Ă���ꍇ
            if (CollisionPair(collisionLine, collModel, collInfoLine))
            {
                // �������Փ˓_�ɍ��킹��
                pos = collInfoLine.HitPosition;

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }

        // �G�l�~�[�Ƃ̏Փ�
        if (tag == ObjectTag::Enemy)
        {
            // �������Ă�����
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // �������v�Z����
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // �����߂��ʂ��v�Z����
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // ���K������
                    pushBack = VNorm(pushBack);

                    // �����߂�
                    pos += pushBack * -dif;
                }

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }

        if (tag == ObjectTag::PlayerBullet)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // �������v�Z����
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // �����߂��ʂ��v�Z����
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // ���K������
                    pushBack = VNorm(pushBack);

                    // �����߂�
                    pos += pushBack * -dif * 100.0f;

                    pos.y += 200.0f;

                    damagePar += 10.0f;
                }

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }
    }

    void BaseEnemy::RotateCheck()
    {
        if (isRotate)
        {
            // ��]���ڕW�p�x�ɏ\���߂���Ή�]�I��
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                isRotate = false;
            }
            else
            {
                // ��]������
                VECTOR interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);

                // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
                VECTOR cross1 = VCross(dir, aimDir);
                VECTOR cross2 = VCross(interPolateDir, aimDir);

                // �ڕW�p�x�𒴂�����I��
                if (cross1.y * cross2.y < 0.0f)
                {
                    interPolateDir = aimDir;
                    isRotate = false;
                }

                // �ڕW�x�N�g����10�x�����߂Â����p�x
                dir = interPolateDir;
            }
        }
    }

    void BaseEnemy::DamageParView()
    {
        VECTOR screenPos = ConvWorldPosToScreenPos(pos);

        DrawFormatString((int)screenPos.x - 10, (int)screenPos.y - 50, GetColor(255, 255, 255), "%1.1f��", damagePar);
    }

    void BaseEnemy::Shot()
    {
        if (shotInterval < 0)
        {
            shotInterval = 1.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBullet, pos, dir));
        }
    }
}// namespace My3dApp