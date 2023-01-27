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

        // 座標の設定
        MV1SetPosition(modelHandle, this->pos);

        // 弾の大きさ
        float bulletSize = 1.0f;

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));

        // 当たり判定球の半径の設定
        collisionSphere.radius = 100.0f;

        // 当たり判定の更新
        CollisionUpdate();
    }

    ChargeBullet::~ChargeBullet()
    {
        AssetManager::ReleaseMesh(modelHandle);
    }

    void ChargeBullet::Update(float deltaTime)
    {
        // キーが押された瞬間
        if (CheckHitKey(KEY_INPUT_K) == 1)
        {
            isCharging = true;
        }
        // キーが押されっぱなし
        if (isCharging && GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_K)
        {
            chargeTime += deltaTime;
        }
        // キーが離された瞬間
        if (CheckHitKey(KEY_INPUT_K) == -1)
        {
            isCharging = false;
            // チャージ時間に応じて、弾を発射する
            if (chargeTime > 5) {
                // チャージ時間が30秒以上だったら強力な弾を発射する
                move = true;
            }
            else {
                // チャージ時間が30秒未満だったら通常の弾を発射する
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