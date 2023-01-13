#include "Enemy.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/AnimationController.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "ObjectTag.h"
#include "Bullet.h"

namespace My3dApp
{
    Enemy::Enemy()
        : Enemy(initPos)
    {
    }

    Enemy::Enemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , animTypeID(0)
        , isRotate(false)
        , turnCount(5.0f)
        , shotInterval(0)
    {
        modelHandle = AssetManager::GetMesh("../asset/model/test/enemy.mv1");

        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        dir = VGet(1, 0, 0);

        aimDir = dir;

        speed = VGet(0, 0, 0);

        collisionType = CollisionType::Sphere;

        collisionSphere.localCenter = VGet(0, 75.0f, 0);

        collisionSphere.radius = 65.0f;

        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        CollisionUpdate();
    }

    Enemy::~Enemy()
    {
        // ���f���̃A�����[�h
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Enemy::Update(float deltaTime)
    {
        Move(deltaTime);
    }

    void Enemy::Draw()
    {
        // ���f���̕`��
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Enemy::OnCollisionEnter(const GameObject* other)
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
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));
                float r1 = collisionSphere.radius;
                float r2 = other->GetCollisionSphere().radius;

                if (r1 + r2 > r)
                {
                    float dif = r1 + r2 - r;

                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;
                    pushBack = VNorm(pushBack);
                    pos += pushBack * -dif;
                }

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }
    }

    void Enemy::Move(float deltaTime)
    {
        // �v���C���[�̎擾
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // �v���C���[�̍��W���玩�g�̍��W�������Č����x�N�g�����v�Z����
        VECTOR tmp = player->GetPos() - pos;

        // �����x�N�g���̖�����
        tmp.y = 0;

        if (VSize(tmp) > 800.0f)
        {
            if (turnCount < 0)
            {
                turnCount = 3.0f;
                dir.x *= -1;
                dir.z *= -1;
            }
            else
            {
                turnCount -= deltaTime;
            }
        }
        // �߂��܂Œǐ�
        else if (VSize(tmp) > 100.0f)
        {

            shotInterval -= deltaTime;

            Shot();

            dir = VNorm(tmp);

            speed =  (dir * deltaTime * 200.0f);

            pos += speed;
        }

        // 3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        // �����ɍ��킹�ă��f������]
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // ���f���ɉ�]���Z�b�g����
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // �����蔻�胂�f���̈ʒu�X�V
        CollisionUpdate();
    }

    void Enemy::RotateCheck()
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

    void Enemy::Shot()
    {
        if (shotInterval < 0)
        {
            shotInterval = 1.0f;
            GameObjectManager::Entry(new Bullet(ObjectTag::EnemyBullet, pos, dir));
        }
    }
}// namespace My3dApp