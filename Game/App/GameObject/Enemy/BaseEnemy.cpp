#include "BaseEnemy.h"
#include "../../Manager/EnemyManager.h"
#include "../../Library/Calc3D.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/GameManager.h"
#include "../Bullet/NormalBullet.h"
#include "../Effect/HitEffect.h"

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
        , isNockBack(false)
        , nockBackDir(VGet(0, 1, 0))
        , weight(0)
        , nockBackPar(0)
        , gravity(10.0f)
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
        GameManager::AddComb();
        GameManager::AddScore(100);
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

        if (pos.y > 0.0f)
        {
            // 蓄積ダメージの表示
            DamageParView();
        }
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

                gravity = 0;

                if (gravity == 0)
                {
                    isNockBack = false;
                }

                // 当たり判定情報の解放
                MV1CollResultPolyDimTerminate(collInfo);

                // 当たり判定の更新
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
                    damagePar += 10.0f;

                    isNockBack = true;

                    gravity = jumpForce;

                    nockBackDir = other->GetDir();

                    if (damagePar > 50)
                    {
                        GameObjectManager::Entry(new HitEffect(pos, 1));
                        
                    }
                    else
                    {
                        GameObjectManager::Entry(new HitEffect(pos, 0));
                    }
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

        SetFontSize(25);

        int cr = GetColor(255, 255, 255);

        if (damagePar >= 100)
        {
            cr = GetColor(161, 21, 8);
        }
        else if (damagePar >= 80)
        {
            cr = GetColor(219, 78, 10);
        }
        else if (damagePar >= 60)
        {
            cr = GetColor(255, 142, 61);
        }
        else if (damagePar >= 40)
        {
            cr = GetColor(252, 167, 10);
        }
        else if (damagePar >= 20)
        {
            cr = GetColor(254, 222, 10);
        }

        DrawFormatString((int)screenPos.x - 20, (int)screenPos.y - 50, cr, "%1.0f％", damagePar);
    }

    bool BaseEnemy::IsDead()
    {
        // 一定以上落下したら
        if (pos.y < -500.0f)
        {
            // 死んでいる
            return true;
        }
        return false;
    }

    void BaseEnemy::Shot(float deltaTime)
    {
        shotInterval -= deltaTime;
        if (shotInterval < 0)
        {
            shotInterval = 5.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBullet, pos, dir));
        }
    }

    void BaseEnemy::KnockBack(float deltaTime)
    {
        // ノックバックする向きを正規化して
        nockBackDir = VNorm(nockBackDir);

        nockBackPar = damagePar * 20.0f;

        speed = (nockBackDir * nockBackPar * deltaTime);

        pos += speed;
    }
}// namespace My3dApp