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
        // モデルの読み込み
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // 位置の初期化
        MV1SetPosition(modelHandle, this->pos);

        // 大きさの初期化
        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        // 向きの初期化
        dir = VGet(1, 0, 0);

        // 目標向きの初期化
        aimDir = dir;

        // 速度の初期化
        speed = VGet(0, 0, 0);

        // 当たり判定種類の初期化
        collisionType = CollisionType::Sphere;

        // 球のローカル中心座標の初期化
        collisionSphere.localCenter = VGet(0, 0, 0);

        // 球の半径の初期化
        collisionSphere.radius = 65.0f;

        // 線形当たり判定の追加
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // 当たり判定の更新
        CollisionUpdate();

        EnemyManager::AddNum();
    }

    Enemy::~Enemy()
    {
        // モデルの後始末
        AssetManager::ReleaseMesh(modelHandle);

        EnemyManager::SubNum();
    }

    void Enemy::Update(float deltaTime)
    {
        // 移動
        Move(deltaTime);
    }

    void Enemy::Draw()
    {
        // モデルの描画
        MV1DrawModel(modelHandle);

        // 当たり判定の描画
        DrawCollider();

        NockBackParView();
    }

    void Enemy::OnCollisionEnter(const GameObject* other)
    {
        // 調べるオブジェクトのタグを取得
        ObjectTag tag = other->GetTag();

        // マップとの衝突
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // マップと自身の境界球との当たり判定
            MV1_COLL_RESULT_POLY_DIM collInfo;

            // 当たっている場合
            if (CollisionPair(collisionSphere, collModel, collInfo))
            {
                // 押し戻し量
                VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(collisionSphere, collInfo);

                // 押し戻し
                pos += pushBackVec;

                onGround = true;

                // 当たり判定情報の解放
                MV1CollResultPolyDimTerminate(collInfo);

                // 当たり判定の更新
                CollisionUpdate();
            }
            else
            {
                onGround = false;

                CollisionUpdate();
            }

            // 背景と足元線分当たり判定
            MV1_COLL_RESULT_POLY collInfoLine;

            // 当たっている場合
            if (CollisionPair(collisionLine, collModel, collInfoLine))
            {
                // 足元を衝突点に合わせる
                pos = collInfoLine.HitPosition;

                // 当たり判定の更新
                CollisionUpdate();
            }
        }

        // エネミーとの衝突
        if (tag == ObjectTag::Enemy)
        {
            // 当たっていたら
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // 差分を計算して
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // 押し戻し量を計算する
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // 正規化して
                    pushBack = VNorm(pushBack);

                    // 押し戻す
                    pos += pushBack * -dif;
                }

                // 当たり判定の更新
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
                    // 差分を計算して
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // 押し戻し量を計算する
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // 正規化して
                    pushBack = VNorm(pushBack);

                    // 押し戻す
                    pos += pushBack * -dif * 100.0f;

                    pos.y += 200.0f;

                    nockBackPar += 10.0f;
                }

                // 当たり判定の更新
                CollisionUpdate();
            }
        }
    }

    void Enemy::Move(float deltaTime)
    {
        // プレイヤーの取得
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // プレイヤーの座標から自身の座標を引いて向きベクトルを計算する
        VECTOR tmp = player->GetPos() - pos;

        // 高さベクトルの無効化
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

        // 3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        // 向きに合わせてモデルを回転
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // 当たり判定モデルの位置更新
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
            // 回転が目標角度に十分近ければ回転終了
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                isRotate = false;
            }
            else
            {
                // 回転させる
                VECTOR interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);

                // 回転が目標角度を超えていないか
                VECTOR cross1 = VCross(dir, aimDir);
                VECTOR cross2 = VCross(interPolateDir, aimDir);

                // 目標角度を超えたら終了
                if (cross1.y * cross2.y < 0.0f)
                {
                    interPolateDir = aimDir;
                    isRotate = false;
                }

                // 目標ベクトルに10度だけ近づけた角度
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

        DrawFormatString((int)screenPos.x - 10, (int)screenPos.y - 50, GetColor(255, 255, 255), "%1.1f％", nockBackPar);
    }
}// namespace My3dApp