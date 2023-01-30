#include "BaseEnemy.h"
#include "../../Manager/EnemyManager.h"
#include "../../Library/Calc3D.h"
#include "../../Manager/GameObjectManager.h"
#include "../Bullet/NormalBullet.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">初期位置</param>
    BaseEnemy::BaseEnemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , dir(VGet(1, 0, 0))
        , aimDir(dir)
        , speed(VGet(0, 0, 0))
        , isRotate(false)
        , shotInterval(2.0f)
        , damagePar(0.0f)
    {
        // 当たり判定種類の設定
        collisionType = CollisionType::Sphere;

        // 球のローカル中心座標の初期化
        collisionSphere.localCenter = VGet(0, 0, 0);

        // 線形当たり判定の追加
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // エネミーの現在数を増やす
        EnemyManager::AddNum();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    BaseEnemy::~BaseEnemy()
    {
        // エネミーの現在数を減らす
        EnemyManager::SubNum();
    }

    /// <summary>
    /// エネミーの描画
    /// </summary>
    void BaseEnemy::Draw()
    {
        // モデルの描画
        MV1DrawModel(modelHandle);

        // 当たり判定の描画
        //DrawCollider();

        // 蓄積ダメージの表示
        DamageParView();
    }

    /// <summary>
    /// 他のオブジェクトと衝突したときのリアクション
    /// </summary>
    /// <param name="other">自分とは異なるオブジェクト</param>
    void BaseEnemy::OnCollisionEnter(const GameObject* other)
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

                    damagePar += 10.0f;
                }

                // 当たり判定の更新
                CollisionUpdate();
            }
        }
    }

    void BaseEnemy::RotateCheck()
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

    void BaseEnemy::DamageParView()
    {
        VECTOR screenPos = ConvWorldPosToScreenPos(pos);

        DrawFormatString((int)screenPos.x - 10, (int)screenPos.y - 50, GetColor(255, 255, 255), "%1.1f％", damagePar);
    }

    void BaseEnemy::Shot()
    {
        if (shotInterval < 0)
        {
            shotInterval = 1.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBullet, pos, dir));
        }
    }
}// namespace My3dApp