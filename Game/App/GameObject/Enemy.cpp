#include "Enemy.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/AssetManager.h"
#include "../Manager/EnemyManager.h"
#include "../Library/AnimationController.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "ObjectTag.h"
#include "Bullet.h"

namespace My3dApp
{
    Enemy::Enemy()
        : Enemy(VGet(0, 0, 0))
    {
    }

    Enemy::Enemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , animTypeID(0)
        , isRotate(false)
        , shotInterval(2.0f)
        , nockBackPar(0.0f)
    {
        // ���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // �ʒu�̏�����
        MV1SetPosition(modelHandle, this->pos);

        // �傫���̏�����
        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        // �����̏�����
        dir = VGet(1, 0, 0);

        // �ڕW�����̏�����
        aimDir = dir;

        // ���x�̏�����
        speed = VGet(0, 0, 0);

        // �����蔻���ނ̏�����
        collisionType = CollisionType::Sphere;

        // ���̃��[�J�����S���W�̏�����
        collisionSphere.localCenter = VGet(0, 0, 0);

        // ���̔��a�̏�����
        collisionSphere.radius = 65.0f;

        // ���`�����蔻��̒ǉ�
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // �����蔻��̍X�V
        CollisionUpdate();

        EnemyManager::AddNum();
    }

    Enemy::~Enemy()
    {
        // ���f���̌�n��
        AssetManager::ReleaseMesh(modelHandle);

        EnemyManager::SubNum();
    }

    void Enemy::Update(float deltaTime)
    {
        // �ړ�
        Move(deltaTime);
    }

    void Enemy::Draw()
    {
        // ���f���̕`��
        MV1DrawModel(modelHandle);

        // �����蔻��̕`��
        DrawCollider();

        NockBackParView();
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

                    nockBackPar += 10.0f;
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

        if (VSize(tmp) > 300.0f)
        {
            shotInterval -= deltaTime;

            Shot();

            dir = VNorm(tmp);

            speed =  (dir * deltaTime * 300.0f);

            if (onGround)
            {
                pos += speed;
            }
        }
        else
        {
            shotInterval -= deltaTime;

            dir = VNorm(tmp);

            Shot();
        }

        if (!onGround)
        {
            speed = (VGet(0, -1, 0) * 10.0f);

            pos += speed;

            CollisionUpdate();
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

        if (pos.y < -500.0f)
        {
            isAlive = false;
        }
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

    void Enemy::NockBackParView()
    {
        VECTOR screenPos = ConvWorldPosToScreenPos(pos);

        DrawFormatString((int)screenPos.x - 10, (int)screenPos.y - 50, GetColor(255, 255, 255), "%1.1f��", nockBackPar);
    }
}// namespace My3dApp