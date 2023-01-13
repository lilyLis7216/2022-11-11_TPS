#include "Bullet.h"
#include "../Manager/AssetManager.h"
#include "../Library/Calc3D.h"

namespace My3dApp
{
    Bullet::Bullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag)
        , deadCount(5.0f)
        , boost(0)
    {
        modelHandle = AssetManager::GetMesh("../asset/model/bullet/bullet.mv1");

        this->pos = pos;

        this->pos.y = 80.0f;

        MV1SetPosition(modelHandle, this->pos);

        MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

        this->dir = dir;

        speed = VGet(0, 0, 0);

        if (tag == ObjectTag::PlayerBullet)
        {
            boost = 800.0f;
        }
        else if (tag == ObjectTag::EnemyBullet)
        {
            boost = 1000.0f;
        }
    }

    Bullet::~Bullet()
    {
    }

    void Bullet::Update(float deltaTime)
    {
        if (deadCount < 0)
        {
            isAlive = false;
        }
        else
        {
            deadCount -= deltaTime;
        }

        speed = dir * deltaTime * boost;

        pos += speed;

        // 3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        // 当たり判定モデルの位置更新
        CollisionUpdate();
    }

    void Bullet::Draw()
    {
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Bullet::OnCollisionEnter(const GameObject* other)
    {
    }
}// namespace My3dApp