#pragma once

#include <DxLib.h>
#include "ObjectTag.h"
#include "../Library/CollisionType.h"
#include "../Library/Collision.h"

namespace My3dApp
{
    class GameObject
    {
    protected:
        /** タグ（オブジェクトの種類）*/
        ObjectTag tag;

        /** モデル*/
        int modelHandle;

        /** 座標*/
        VECTOR pos;

        /** 座標の初期値*/
        VECTOR initPos = VGet(0, 0, 0);

        /** 可視状態*/
        bool visible;

        /** 生死状態*/
        bool alive;

        /** 当たり判定の種類*/
        CollisionType collisionType;

        /** 線分当たり判定*/
        LineSegment collisionLine;

        /** 球体当たり判定*/
        Sphere collisionSphere;

        /** カプセル当たり判定*/
        Capsule collisionCapsule;

        /** モデル当たり判定*/
        int collisionModel;

        /** 当たり判定の描画*/
        void DrawCollider();

        /** 当たり判定位置の更新*/
        void CollisionUpdate();

    public:
        /** コンストラクタ（タグのみ）*/
        GameObject(ObjectTag tag);

        /** コンストラクタ（タグ、位置指定）*/
        GameObject(ObjectTag tag, VECTOR pos);

        /** 仮想デストラクタ*/
        virtual ~GameObject();

        /** 更新処理（純粋仮想関数）*/
        virtual void Update(float deltaTime) = 0;

        /** 描画処理（仮想関数）*/
        virtual void Draw();

        /** オブジェクトタグの取得*/
        ObjectTag GetTag() const { return tag; }

        /** 位置の取得*/
        const VECTOR& GetPos() const { return pos; }

        /** 位置の指定*/
        void SetPos(const VECTOR set) { pos = set; }

        /** 可視状態の取得*/
        bool GetVisible() const { return visible; }

        /** 可視状態の指定*/
        void SetVisible(bool visible) { this->visible = visible; }

        /** 生死状態の取得*/
        bool GetAlive() const { return alive; }

        /** 生死状態の指定*/
        void SetAlive(bool alive) { this->alive = alive; }

        /** 他のオブジェクトと衝突したときのリアクション*/
        virtual void OnCollisionEnter(const GameObject* other) {};

        /** このオブジェクトとの当たり判定*/
        virtual void Collision(GameObject* other) {};

        /** 当たり判定種類の取得*/
        CollisionType GetCollisionType() const { return collisionType; }

        /** 線分当たり判定の取得*/
        LineSegment GetCollisionLine() const { return collisionLine; }

        /** 球体当たり判定の取得*/
        Sphere GetCollisionSphere() const { return collisionSphere; }

        /** カプセル当たり判定の取得*/
        Capsule GetCollisionCapsule() const { return collisionCapsule; }

        /** モデル当たり判定の取得*/
        int GetCollisionModel() const { return collisionModel; }
    };
}/** namespace My3dApp*/