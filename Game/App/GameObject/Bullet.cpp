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
        modelHandle = -1;

        if (this->tag == ObjectTag::PlayerBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/playerBullet.mv1");
        }
        else if (this->tag == ObjectTag::EnemyBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/enemyBullet.mv1");
        }

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

        // 当たり判定種類の初期化
        collisionType = CollisionType::Sphere;

        // 球のローカル中心座標の初期化
        collisionSphere.localCenter = VGet(0, 0, 0);

        // 球の半径の初期化
        collisionSphere.radius = 10.0f;

        // 当たり判定の更新
        CollisionUpdate();
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

        //DrawCollider();
    }

    void Bullet::OnCollisionEnter(const GameObject* other)
    {
        // 調べるオブジェクトのタグを取得
        ObjectTag tag = other->GetTag();

        // 自身がプレイヤー弾であれば
        if (this->tag == ObjectTag::PlayerBullet)
        {
            // エネミーとの当たり判定
            if (tag == ObjectTag::Enemy)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }

        // 自身がエネミー弾であれば
        if (this->tag == ObjectTag::EnemyBullet)
        {
            // プレイヤーとの当たり判定
            if (tag == ObjectTag::Player)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }
    }
}// namespace My3dApp