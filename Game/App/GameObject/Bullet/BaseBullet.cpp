#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">オブジェクトの種類</param>
    BaseBullet::BaseBullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag, pos)
        , speed(VGet(0, 0, 0))
        , bulletType(-1)
        , radius(0)
        , divNum(16)
        , difColor(-1)
        , spcColor(-1)
        , isFill(true)
        , vanishCount(5.0f)
        , boost(0)
    {
        // 向きを設定
        this->dir = dir;

        // 当たり判定種類の設定
        collisionType = CollisionType::Sphere;

        // 当たり判定球のローカル座標の初期化
        collisionSphere.localCenter = VGet(0, 0, 0);
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
        // 球の描画
        DrawSphere3D(pos, collisionSphere.radius, divNum, difColor, spcColor, isFill);

        // 当たり判定の描画
        DrawCollider();
    }
}// namespace My3dApp