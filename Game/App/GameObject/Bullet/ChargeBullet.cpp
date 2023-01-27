#include "ChargeBullet.h"
#include "../../Manager/AssetManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    ChargeBullet::ChargeBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : BaseBullet(tag,pos,dir)
        , chargeState(0)
        , prevPush(false)
        , chargeTime(5.0f)
        , move(false)
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

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // �e�̑傫��
        float bulletSize = 1.0f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 100.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    ChargeBullet::~ChargeBullet()
    {
        AssetManager::ReleaseMesh(modelHandle);
    }

    void ChargeBullet::Update(float deltaTime)
    {
        // �L�[�������ꂽ�u��
        if (CheckHitKey(KEY_INPUT_K) == 1)
        {
            isCharging = true;
        }
        // �L�[����������ςȂ�
        if (isCharging && GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_K)
        {
            chargeTime += deltaTime;
        }
        // �L�[�������ꂽ�u��
        if (CheckHitKey(KEY_INPUT_K) == -1)
        {
            isCharging = false;
            // �`���[�W���Ԃɉ����āA�e�𔭎˂���
            if (chargeTime > 5) {
                // �`���[�W���Ԃ�30�b�ȏゾ�����狭�͂Ȓe�𔭎˂���
                move = true;
            }
            else {
                // �`���[�W���Ԃ�30�b������������ʏ�̒e�𔭎˂���
                move = false;
            }
            chargeTime = 0;
        }

        if (move)
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