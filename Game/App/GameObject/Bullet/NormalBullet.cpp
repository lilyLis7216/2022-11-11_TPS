#include "NormalBullet.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"
#include "../Effect/HitEffect.h"

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
        // オブジェクトの種類がプレイヤー弾なら
        if (tag == ObjectTag::PlayerBullet)
        {
            difColor = GetColor(0, 0, 255);
            boost = 800.0f;
        }
        // オブジェクトの種類がエネミー弾なら
        else if (tag == ObjectTag::EnemyBullet)
        {
            difColor = GetColor(255, 0, 0);
            boost = 1000.0f;
        }

        // 弾の半径の設定
        radius = 25.0f;

        // 当たり判定球の半径の設定
        collisionSphere.radius = radius;

        // 当たり判定の更新
        CollisionUpdate();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    NormalBullet::~NormalBullet()
    {
        // 処理なし
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