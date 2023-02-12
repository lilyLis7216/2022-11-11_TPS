#include "HeavyEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"
#include "../Bullet/NormalBullet.h"

namespace My3dApp
{
    HeavyEnemy::HeavyEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        enemyType = 2;

        // モデルの読み込み
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // 座標の設定
        MV1SetPosition(modelHandle, this->pos);

        // モデルの大きさ
        float modelSize = 1.0f;

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // 当たり判定球の半径の設定
        collisionSphere.radius = 100.0f;

        weight = 1000.0f;

        // 当たり判定の更新
        CollisionUpdate();
    }

    HeavyEnemy::~HeavyEnemy()
    {
        // モデルの後始末
        AssetManager::ReleaseMesh(modelHandle);
    }
    void HeavyEnemy::Update(float deltaTime)
    {
        if (isNockBack)
        {
            // ノックバック処理
            KnockBack(deltaTime);
        }
        else
        {
            // 移動
            Move(deltaTime);

            if (canShot)
            {
                // 射撃
                Shot(deltaTime);
            }
        }

        gravity -= weight * deltaTime;

        pos.y += gravity * deltaTime;

        // 向きに合わせてモデルを回転
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // 3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        // 当たり判定モデルの位置更新
        CollisionUpdate();

        if (IsDead())
        {
            isAlive = false;
        }
    }

    void HeavyEnemy::Move(float deltaTime)
    {
        // プレイヤーの取得
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // プレイヤーの座標から自身の座標を引いて向きベクトルを計算する
        VECTOR tmp = player->GetPos() - pos;

        // 高さベクトルの無効化
        tmp.y = 0;

        dir = VNorm(tmp);

        if (VSize(tmp) > 1000.0f)
        {
            speed = (dir * deltaTime * 100.0f);

            pos += speed;

            canShot = false;
        }
        else if (VSize(tmp) > 300.0f)
        {
            speed = (dir * deltaTime * 100.0f);

            pos += speed;

            canShot = true;
        }
    }

    void HeavyEnemy::Shot(float deltaTime)
    {
        shotInterval -= deltaTime;
        if (shotInterval < 0)
        {
            shotInterval = 5.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBulletL, pos, dir));
        }
    }
}// namespace My3dApp