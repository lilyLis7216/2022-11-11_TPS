#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">オブジェクトの種類</param>
    BaseBullet::BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag, pos)
        , dir(dir)
        , speed(VGet(0, 0, 0))
        , vanishCount(5.0f)
        , boost(0)
        , bulletType(-1)
    {
        // 当たり判定種類の設定
        collisionType = CollisionType::Sphere;

        // 当たり判定球のローカル座標の初期化
        collisionSphere.localCenter = VGet(0, 0, 0);

        // 当たり判定球のワールド座標の初期化
        collisionSphere.worldCenter = this->pos;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    BaseBullet::~BaseBullet()
    {
        // 処理なし
    }

    /// <summary>
    /// 弾の描画
    /// </summary>
    void BaseBullet::Draw()
    {
        // モデルの描画
        MV1DrawModel(modelHandle);

        // 当たり判定の描画(必要な場合非コメント化)
        //DrawCollider();
    }
}// namespace My3dApp