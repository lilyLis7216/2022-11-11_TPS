#pragma once

#include "DxLib.h"
#include "ObjectTag.h"
#include "../Library/CollisionType.h"
#include "../Library/Collision.h"

namespace My3dApp
{
    /// <summary>
    /// ゲームオブジェクト（基底クラス）
    /// </summary>
    class GameObject
    {
    protected:
        // タグ（オブジェクトの種類）
        ObjectTag tag;

        // モデル
        int modelHandle;

        // オブジェクトの座標
        VECTOR pos;

        // 可視状態
        bool isVisible;

        // 生死状態
        bool isAlive;

        // 地上にいるかどうか
        bool onGround;

        // 当たり判定の種類
        CollisionType collisionType;

        // 線分当たり判定
        LineSegment collisionLine;

        // 球体当たり判定
        Sphere collisionSphere;

        // カプセル当たり判定
        Capsule collisionCapsule;

        // モデル当たり判定
        int collisionModel;

        // 当たり判定の描画
        void DrawCollider();

        // 当たり判定位置の更新
        void CollisionUpdate();

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトのタグ</param>
        GameObject(ObjectTag tag);

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトのタグ</param>
        /// <param name="pos">初期位置</param>
        GameObject(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// 仮想デストラクタ
        /// </summary>
        virtual ~GameObject();

        /// <summary>
        /// ゲームオブジェクトの更新（純粋仮想関数）
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        virtual void Update(float deltaTime) = 0;

        /// <summary>
        /// ゲームオブジェクトの描画（仮想関数）
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// オブジェクトのタグの取得
        /// </summary>
        /// <returns>オブジェクトが持っているタグ</returns>
        ObjectTag GetTag() const { return tag; }

        /// <summary>
        /// 位置の取得
        /// </summary>
        /// <returns>オブジェクトの現在位置</returns>
        const VECTOR& GetPos() const { return pos; }

        /// <summary>
        /// 位置の変更
        /// </summary>
        /// <param name="set">変更したい位置</param>
        void SetPos(const VECTOR set) { pos = set; }

        /// <summary>
        /// 可視状態の取得
        /// </summary>
        /// <returns>可視ならtrue 不可視ならfalse</returns>
        bool GetVisible() const { return isVisible; }

        /// <summary>
        /// 可視状態の変更
        /// </summary>
        /// <param name="set">変更したい状態</param>
        void SetVisible(bool set) { isVisible = set; }

        /// <summary>
        /// 生死状態の取得
        /// </summary>
        /// <returns>生きていたらtrue 死んでいたらfalse</returns>
        bool GetAlive() const { return isAlive; }

        /// <summary>
        /// 生死状態の変更
        /// </summary>
        /// <param name="set">変更したい状態</param>
        void SetAlive(bool set) { isAlive = set; }

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        virtual void OnCollisionEnter(const GameObject* other) {};

        /// <summary>
        /// このオブジェクトとの当たり判定
        /// </summary>
        /// <param name="other">当たり判定を調べたいオブジェクト</param>
        virtual void Collision(GameObject* other) {};

        /// <summary>
        /// 当たり判定種類の取得
        /// </summary>
        /// <returns>オブジェクトが持っている当たり判定種類</returns>
        CollisionType GetCollisionType() const { return collisionType; }

        /// <summary>
        /// 線分当たり判定の取得
        /// </summary>
        /// <returns>線分の当たり判定</returns>
        LineSegment GetCollisionLine() const { return collisionLine; }

        /// <summary>
        /// 球体当たり判定の取得
        /// </summary>
        /// <returns>球体の当たり判定</returns>
        Sphere GetCollisionSphere() const { return collisionSphere; }

        /// <summary>
        /// カプセル当たり判定の取得
        /// </summary>
        /// <returns>カプセルの当たり判定</returns>
        Capsule GetCollisionCapsule() const { return collisionCapsule; }

        /// <summary>
        /// モデル当たり判定の取得
        /// </summary>
        /// <returns>モデルの当たり判定</returns>
        int GetCollisionModel() const { return collisionModel; }

    };
}// namespace My3dApp