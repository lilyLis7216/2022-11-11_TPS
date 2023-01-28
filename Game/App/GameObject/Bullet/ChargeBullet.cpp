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
        // 弾の種類をノーマル弾に設定
        bulletType = Charge;

        // オブジェクトの種類がプレイヤー弾なら
        if (tag == ObjectTag::PlayerBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/playerBullet.mv1");
            boost = 800.0f;
        }
        // オブジェクトの種類がエネミー弾なら
        else if (tag == ObjectTag::EnemyBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/enemyBullet.mv1");
            boost = 1000.0f;
        }

        this->pos.y += 100.0f;

        // 座標の設定
        MV1SetPosition(modelHandle, this->pos);

        // 弾の大きさ
        float bulletSize = 0.25f;

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));

        // 当たり判定球の半径の設定
        collisionSphere.radius = 0.26f;

        // 当たり判定の更新
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
                    // 弾の大きさ
                    float bulletSize = 1.0f;

                    // 大きさの設定
                    MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));
                    collisionSphere.radius = 100.0f;
                }
                else if (chargeTime > 1.0f)
                {
                    // 弾の大きさ
                    float bulletSize = 0.5f;

                    // 大きさの設定
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

        // モデルの位置の更新
        MV1SetPosition(modelHandle, pos);

        // 当たり判定の更新
        CollisionUpdate();
    }

    void ChargeBullet::OnCollisionEnter(const GameObject* other)
    {
        // 調べるオブジェクトの種類を取得
        ObjectTag searchTag = other->GetTag();

        // 自身がプレイヤー弾であれば
        if (tag == ObjectTag::PlayerBullet)
        {
            // エネミーとの当たり判定
            if (searchTag == ObjectTag::Enemy)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }

        // 自身がエネミー弾であれば
        if (tag == ObjectTag::EnemyBullet)
        {
            // プレイヤーとの当たり判定
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