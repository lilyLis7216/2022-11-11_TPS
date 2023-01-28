#include "ChargeBullet.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    ChargeBullet::ChargeBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : BaseBullet(tag,pos,dir)
        , isCharging(false)
        , chargeTime(0)
        , canMove(false)
        , isShoot(false)
    {
        // �e�̎�ނ��m�[�}���e�ɐݒ�
        bulletType = Charge;

        // �I�u�W�F�N�g�̎�ނ��v���C���[�e�Ȃ�
        if (tag == ObjectTag::PlayerBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/playerBullet.mv1");
            boost = 800.0f;
        }
        // �I�u�W�F�N�g�̎�ނ��G�l�~�[�e�Ȃ�
        else if (tag == ObjectTag::EnemyBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/enemyBullet.mv1");
            boost = 1000.0f;
        }

        this->pos.y += 100.0f;

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // �e�̑傫��
        float bulletSize = 0.25f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 0.26f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    ChargeBullet::~ChargeBullet()
    {
        AssetManager::ReleaseMesh(modelHandle);
    }

    void ChargeBullet::Update(float deltaTime)
    {
        GetHitKeyStateAllEx(key);

        if (key[KEY_INPUT_K] == 1)
        {
        }
        else if (key[KEY_INPUT_K] > 1)
        {
            chargeTime += deltaTime;

            if (!isShoot)
            {
                GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

                pos = player->GetPos();

                pos.y += 100.0f;

                MV1SetPosition(modelHandle, pos);

                dir = player->GetDir();

                if (chargeTime > 2.0f)
                {
                    // �e�̑傫��
                    float bulletSize = 1.0f;

                    // �傫���̐ݒ�
                    MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));
                    collisionSphere.radius = 100.0f;
                }
                else if (chargeTime > 1.0f)
                {
                    // �e�̑傫��
                    float bulletSize = 0.5f;

                    // �傫���̐ݒ�
                    MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));
                    collisionSphere.radius = 50.0f;
                }
            }
        }
        else if (key[KEY_INPUT_K] == -1)
        {
            isShoot = true;
            if (chargeTime > 1.0f)
            {
                canMove = true;
            }
            else
            {
                isAlive = false;
            }
        }

        if (canMove)
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
        }

        // ���f���̈ʒu�̍X�V
        MV1SetPosition(modelHandle, pos);

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    void ChargeBullet::OnCollisionEnter(const GameObject* other)
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
}