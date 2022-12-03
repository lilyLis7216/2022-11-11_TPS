#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /**
    * 線分当たり判定
    */
    struct LineSegment
    {
        /** */
        LineSegment();

        /** */
        LineSegment(const VECTOR& startPos, const VECTOR& endPos);

        /** 線分当たり判定の移動*/
        void Move(const VECTOR& pos);

        /** 線分のローカル始点座標*/
        VECTOR localStart;

        /** 線分のローカル終点座標*/
        VECTOR localEnd;

        /** 線分のワールド始点座標*/
        VECTOR worldStart;

        /** 線分のワールド終点座標*/
        VECTOR worldEnd;
    };

    /**
    * 球体当たり判定
    */
    struct Sphere
    {
        /** */
        Sphere();

        /** */
        Sphere(const VECTOR& center, float r);

        /** 球体当たり判定の移動*/
        void Move(const VECTOR& pos);

        /** 球体のローカル中心座標*/
        VECTOR localCenter;

        /** 球体のワールド中心座標*/
        VECTOR worldCenter;

        /** 球体の半径*/
        float radius;
    };

    /**
    * カプセル当たり判定
    */
    struct Capsule
    {
        /** */
        Capsule();

        /** */
        Capsule(const VECTOR& start, const VECTOR& end, float r);

        /** カプセル当たり判定の移動*/
        void Move(const VECTOR& pos);

        /** カプセルのローカル始点座標*/
        VECTOR localStart;

        /** カプセルのローカル終点座標*/
        VECTOR localEnd;

        /** カプセルのワールド始点座標*/
        VECTOR worldStart;

        /** カプセルのワールド終点座標*/
        VECTOR worldEnd;

        /** カプセルの半径*/
        float radius;
    };

    /** 球体対球体の当たり判定*/
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB);

    /** 線分対球体の当たり判定*/
    bool CollisionPair(const LineSegment& line, const Sphere& sphere);

    /** 球体対線分の当たり判定*/
    bool CollisionPair(const Sphere& sphere, const LineSegment& line);

    /** 球体対メッシュの当たり判定*/
    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);

    /** 線分対メッシュの当たり判定*/
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

    /** メッシュ対線分の当たり判定*/
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo);

    /** 球体とメッシュとの判定後の押し戻し量計算*/
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);

}/** namespace My3dApp*/