#include "Collision.h"
#include "Calc3D.h"

namespace My3dApp
{
    LineSegment::LineSegment()
        : localStart()
        , localEnd()
        , worldStart()
        , worldEnd()
    {
    }

    LineSegment::LineSegment(const VECTOR& startPos, const VECTOR& endPos)
        : localStart(startPos)
        , localEnd(endPos)
        , worldStart(startPos)
        , worldEnd(endPos)
    {
    }

    void LineSegment::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    Sphere::Sphere()
        : localCenter()
        , worldCenter()
        , radius(0.0f)
    {
    }

    Sphere::Sphere(const VECTOR& center, float r)
        : localCenter(center)
        , worldCenter(center)
        , radius(r)
    {
    }

    void Sphere::Move(const VECTOR& pos)
    {
        worldCenter = localCenter + pos;
    }

    Capsule::Capsule()
        : localStart()
        , localEnd()
        , worldStart()
        , worldEnd()
        , radius(0.0f)
    {
    }

    Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float r)
        : localStart(startPos)
        , localEnd(endPos)
        , worldStart(startPos)
        , worldEnd(endPos)
        , radius(r)
    {
    }

    void Capsule::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB)
    {
        return HitCheck_Sphere_Sphere(sphereA.worldCenter, sphereA.radius, sphereB.worldCenter, sphereB.radius);
    }

    bool CollisionPair(const LineSegment& line, const Sphere& sphere)
    {
        return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
    }

    bool CollisionPair(const Sphere& sphere, const LineSegment& line)
    {
        return CollisionPair(line, sphere);
    }

    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.radius);
        if (collisionInfo.HitNum == 0)
        {
            return false;
        }
        return true;
    }

    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.worldStart, line.worldEnd);
        return collisionInfo.HitFlag;
    }

    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        return CollisionPair(line, modelHandle, collisionInfo);
    }

    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        // 衝突球
        // 球中心候補
        VECTOR moveCandidate = sphere.worldCenter;

        // 球半径
        float radius = sphere.radius;

        // ポリゴン平面法線
        VECTOR planeNormal;

        // 移動ベクトル
        VECTOR moveVec = VGet(0, 0, 0);

        // 移動量
        float moveLen = 0.0f;

        // 移動候補
        VECTOR newCenter = sphere.worldCenter;

        // 衝突ポリゴンをすべて回って、球のめり込みを解消する
        for (int i = 0; i < collisionInfo.HitNum; ++i)
        {
            // 衝突ポリゴンの辺1
            VECTOR edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];

            // 衝突ポリゴンの辺2
            VECTOR edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            // 衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
            planeNormal = VCross(edge1, edge2);
            planeNormal = VNorm(planeNormal);

            // 球中心に最も近いポリゴン平面の点を求める
            VECTOR tmp = moveCandidate - collisionInfo.Dim[i].Position[0];
            float dot = VDot(planeNormal, tmp);

            // 衝突点
            VECTOR hitPos = moveCandidate - planeNormal * dot;

            // 球がどれくらいめり込んでいるかを算出
            VECTOR tmp2 = moveCandidate - hitPos;
            float len = VSize(tmp2);

            // めり込んでいる場合は球の中心を押し戻し
            if (HitCheck_Sphere_Triangle(moveCandidate, radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                // めり込み解消する位置まで移動
                len = radius - len;
                moveVec = planeNormal * len;
                moveCandidate += moveVec;
            }
        }

        // 移動候補を移動位置にする
        newCenter = moveCandidate;

        // 押し戻し量を返却
        return newCenter - sphere.worldCenter;
    }
}// namespace My3dApp