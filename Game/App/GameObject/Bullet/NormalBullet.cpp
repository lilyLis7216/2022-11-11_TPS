#include "NormalBullet.h"
#include "../../Manager/AssetManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">オブジェクトの種類</param>
    /// <param name="pos">初期座標</param>
    /// <param name="dir">初期向き</param>
    NormalBullet::NormalBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : BaseBullet(tag, pos, dir)
    {
        // 弾の種類をノーマル弾に設定
        bulletType = Normal;

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
        float bulletSize = 0.25f;

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(bulletSize, bulletSize, bulletSize));

        // 当たり判定球の半径の設定
        collisionSphere.radius = 10.0f;

        // 当たり判定の更新
        CollisionUpdate();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    NormalBullet::~NormalBullet()
    {
        MV1DeleteModel(modelHandle);
    }

    /// <summary>
    /// ノーマル弾の更新
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void NormalBullet::Update(float deltaTime)
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

        // モデルの位置の更新
        MV1SetPosition(modelHandle, pos);

        // 当たり判定の更新
        CollisionUpdate();
    }

    /// <summary>
    /// 他のオブジェクトと衝突したときのリアクション
    /// </summary>
    /// <param name="other">自分とは異なるオブジェクト</param>
    void NormalBullet::OnCollisionEnter(const GameObject* other)
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
}// namespace My3dApp