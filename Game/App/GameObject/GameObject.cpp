#include "GameObject.h"

namespace My3dApp
{
    /** コンストラクタ（タグのみ）
    *
    * @param[in] tag オブジェクトのタグ
    */
    GameObject::GameObject(ObjectTag tag)
        : GameObject(tag, initPos)
    {
    }

    /** コンストラクタ（タグ、位置指定）
    *
    * @param[in] tag オブジェクトのタグ
    * @param[in] pos オブジェクトの位置
    */
    GameObject::GameObject(ObjectTag tag, VECTOR pos)
        : tag(tag)
        , modelHandle(-1)
        , visible(true)
        , alive(true)
        , collisionType()
        , collisionLine()
        , collisionSphere()
        , collisionCapsule()
        , collisionModel()
    {
        this->pos = pos;
    }

    /**
    * 仮想デストラクタ
    */
    GameObject::~GameObject()
    {
        /** モデルの後始末*/
        if (modelHandle == -1)
        {
            modelHandle = -1;
        }
    }

    /**
    * 描画
    */
    void GameObject::Draw()
    {
        /** 処理なし*/
    }

    void GameObject::DrawCollider()
    {
        /** 線分当たり判定の描画*/
        DrawLine3D(collisionLine.worldStart, collisionLine.worldEnd, GetColor(255, 255, 0));

        /** 球体当たり判定の描画*/
        DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);

        /** カプセル当たり判定の描画*/
        DrawCapsule3D(collisionCapsule.worldStart, collisionCapsule.worldEnd, collisionCapsule.radius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);

        /** 当たり判定モデルが存在する場合は半透明描画*/
        if (collisionModel != -1)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(collisionModel);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }

    void GameObject::CollisionUpdate()
    {
        collisionSphere.Move(pos);

        collisionLine.Move(pos);

        collisionCapsule.Move(pos);

        /** モデルの当たり判定情報を再構築*/
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);

            MV1SetupCollInfo(collisionModel);
        }
    }
}/** namespace My3dApp*/