#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// 線分当たり判定
    /// </summary>
    struct LineSegment
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        LineSegment();

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="startPos">初期始点座標</param>
        /// <param name="endPos">初期終点座標</param>
        LineSegment(const VECTOR& startPos, const VECTOR& endPos);

        /** 線分当たり判定の移動*/

        /// <summary>
        /// 線分当たり判定の移動
        /// </summary>
        /// <param name="pos">移動座標</param>
        void Move(const VECTOR& pos);

        // 線分のローカル始点座標
        VECTOR localStart;

        // 線分のローカル終点座標
        VECTOR localEnd;

        // 線分のワールド始点座標
        VECTOR worldStart;

        // 線分のワールド終点座標
        VECTOR worldEnd;

    };

    /// <summary>
    /// 球体当たり判定
    /// </summary>
    struct Sphere
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Sphere();

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="center">中心座標</param>
        /// <param name="r">半径</param>
        Sphere(const VECTOR& center, float r);

        /// <summary>
        /// 球体当たり判定の移動
        /// </summary>
        /// <param name="pos">移動座標</param>
        void Move(const VECTOR& pos);

        // 球体のローカル中心座標
        VECTOR localCenter;

        // 球体のワールド中心座標
        VECTOR worldCenter;

        // 球体の半径
        float radius;

    };

    /// <summary>
    /// カプセル当たり判定
    /// </summary>
    struct Capsule
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Capsule();

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="start">初期始点座標</param>
        /// <param name="end">初期終点座標</param>
        /// <param name="r">半径</param>
        Capsule(const VECTOR& start, const VECTOR& end, float r);

        /// <summary>
        /// カプセル当たり判定の移動
        /// </summary>
        /// <param name="pos">移動座標</param>
        void Move(const VECTOR& pos);

        // カプセルのローカル始点座標
        VECTOR localStart;

        // カプセルのローカル終点座標
        VECTOR localEnd;

        // カプセルのワールド始点座標
        VECTOR worldStart;

        // カプセルのワールド終点座標
        VECTOR worldEnd;

        // カプセルの半径
        float radius;

    };

    /// <summary>
    /// 球体対球体の当たり判定
    /// </summary>
    /// <param name="sphereA">球体A</param>
    /// <param name="sphereB">球体B</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB);

    /// <summary>
    /// 線分対球体の当たり判定
    /// </summary>
    /// <param name="line">線分</param>
    /// <param name="sphere">球体</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const LineSegment& line, const Sphere& sphere);

    /// <summary>
    /// 球体対線分の当たり判定
    /// </summary>
    /// <param name="sphere">球体</param>
    /// <param name="line">線分</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const Sphere& sphere, const LineSegment& line);

    /// <summary>
    /// 球体 対 メッシュ の当たり判定
    /// </summary>
    /// <param name="sphere">球体</param>
    /// <param name="modelHandle">メッシュのモデルID</param>
    /// <param name="collisionInfo">当たった場合のポリゴン数、ポリゴンリスト</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);

    /// <summary>
    /// 線分対メッシュの当たり判定
    /// </summary>
    /// <param name="line">線分</param>
    /// <param name="modelHandle">メッシュのモデルID</param>
    /// <param name="collisionInfo">当たった場合のポリゴン数、ポリゴンリスト</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

    /// <summary>
    /// メッシュ対線分の当たり判定
    /// </summary>
    /// <param name="modelHandle">メッシュのモデルID</param>
    /// <param name="line">線分</param>
    /// <param name="collisionInfo">当たった場合のポリゴン数、ポリゴンリスト</param>
    /// <returns>衝突している場合はtrueを返す</returns>
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo);

    /// <summary>
    /// 球体とメッシュとの判定後の押し戻し量計算
    /// </summary>
    /// <param name="sphere">球体</param>
    /// <param name="collisionInfo">MV1CollCheck_Sphere()関数が返す衝突情報</param>
    /// <returns>球体がメッシュから離れる向きの移動ベクトルを返す</returns>
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);

}// namespace My3dApp