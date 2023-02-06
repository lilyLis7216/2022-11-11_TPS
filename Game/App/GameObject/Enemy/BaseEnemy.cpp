#include "BaseEnemy.h"
#include "../../Manager/EnemyManager.h"
#include "../../Library/Calc3D.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/GameManager.h"
#include "../Bullet/NormalBullet.h"
#include "../Effect/HitEffect.h"

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
        , isNockBack(false)
        , nockBackDir(VGet(0, 1, 0))
        , weight(0)
        , nockBackPar(0)
        , gravity(10.0f)
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
        GameManager::AddComb();
        GameManager::AddScore(100);
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

        if (pos.y > 0.0f)
        {
            // �~�σ_���[�W�̕\��
            DamageParView();
        }
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

                gravity = 0;

                if (gravity == 0)
                {
                    isNockBack = false;
                }

                // �����蔻����̉��
                MV1CollResultPolyDimTerminate(collInfo);

                // �����蔻��̍X�V
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
                    damagePar += 10.0f;

                    isNockBack = true;

                    gravity = jumpForce;

                    nockBackDir = other->GetDir();

                    if (damagePar > 50)
                    {
                        GameObjectManager::Entry(new HitEffect(pos, 1));
                        
                    }
                    else
                    {
                        GameObjectManager::Entry(new HitEffect(pos, 0));
                    }
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

        SetFontSize(25);

        int cr = GetColor(255, 255, 255);

        if (damagePar >= 100)
        {
            cr = GetColor(161, 21, 8);
        }
        else if (damagePar >= 80)
        {
            cr = GetColor(219, 78, 10);
        }
        else if (damagePar >= 60)
        {
            cr = GetColor(255, 142, 61);
        }
        else if (damagePar >= 40)
        {
            cr = GetColor(252, 167, 10);
        }
        else if (damagePar >= 20)
        {
            cr = GetColor(254, 222, 10);
        }

        DrawFormatString((int)screenPos.x - 20, (int)screenPos.y - 50, cr, "%1.0f��", damagePar);
    }

    bool BaseEnemy::IsDead()
    {
        // ���ȏ㗎��������
        if (pos.y < -500.0f)
        {
            // ����ł���
            return true;
        }
        return false;
    }

    void BaseEnemy::Shot(float deltaTime)
    {
        shotInterval -= deltaTime;
        if (shotInterval < 0)
        {
            shotInterval = 5.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBullet, pos, dir));
        }
    }

    void BaseEnemy::KnockBack(float deltaTime)
    {
        // �m�b�N�o�b�N��������𐳋K������
        nockBackDir = VNorm(nockBackDir);

        nockBackPar = damagePar * 20.0f;

        speed = (nockBackDir * nockBackPar * deltaTime);

        pos += speed;
    }
}// namespace My3dApp