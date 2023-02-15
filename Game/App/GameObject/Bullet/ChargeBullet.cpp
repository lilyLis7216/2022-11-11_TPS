#include "ChargeBullet.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/AssetManager.h"
#include "../../Library/Calc3D.h"
#include "../../Library/GamePad.h"
#include "../Effect/HitEffect.h"

namespace My3dApp
{
    ChargeBullet::ChargeBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : BaseBullet(tag, pos, dir)
        , isCharging(false)
        , chargeTime(0)
        , canMove(false)
        , isShoot(false)
        , se1(false)
        , se2(false)
    {
        difColor = GetColor(0, 0, 255);

        boost = 800.0f;

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 10.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    ChargeBullet::~ChargeBullet()
    {
        // �����Ȃ�
    }

    void ChargeBullet::Update(float deltaTime)
    {
        if (GamePad::GetButtonState(Button::B) > 1)
        {
            chargeTime += deltaTime;

            if (!isShoot)
            {
                GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

                pos = player->GetPos() + player->GetDir() * 150.0f;

                pos.y += 25.0f;

                dir = player->GetDir();

                if (chargeTime > 2.0f)
                {
                    collisionSphere.radius = 100.0f;
                }
                else if (chargeTime > 1.0f)
                {
                    if (!se1)
                    {
                        AssetManager::PlaySoundEffect("charge", false);
                        se1 = true;
                    }
                    collisionSphere.radius = 50.0f;
                }
            }
        }
        else if (GamePad::GetButtonState(Button::B) == -1)
        {
            isShoot = true;
            if (chargeTime > 1.0f)
            {
                if (!se2)
                {
                    AssetManager::PlaySoundEffect("chargeShot", false);
                    se2 = true;
                }
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

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    void ChargeBullet::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̎�ނ��擾
        ObjectTag searchTag = other->GetTag();

        // �G�l�~�[�Ƃ̓����蔻��
        if (searchTag == ObjectTag::Enemy)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                isAlive = false;
            }
        }
    }
}