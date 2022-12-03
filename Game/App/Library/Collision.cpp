#include "Collision.h"
#include "Calc3D.h"

namespace My3dApp
{
    /**
    * 線分当たり判定のコンストラクタ
    */
    LineSegment::LineSegment()
        : localStart()
        , localEnd()
        , worldStart()
        , worldEnd()
    {
    }

    /**
    * 線分当たり判定のコンストラクタ
    * 
    * @param[in] startPos 始点初期座標
    * @param[in] endPos   終点初期座標
    */
    LineSegment::LineSegment(const VECTOR& startPos, const VECTOR& endPos)
        : localStart(startPos)
        , localEnd(endPos)
        , worldStart(startPos)
        , worldEnd(endPos)
    {
    }

    /**
    * 線分当たり判定の移動
    * 
    * @param[in] pos 移動座標
    */
    void LineSegment::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    /**
    * 球体当たり判定のコンストラクタ
    */
    Sphere::Sphere()
        : localCenter()
        , worldCenter()
        , radius(0.0f)
    {
    }

    /**
    * 球体当たり判定のコンストラクタ
    * 
    * @param[in] center 中心座標
    * @param[in] r      半径
    */
    Sphere::Sphere(const VECTOR& center, float r)
        : localCenter(center)
        , worldCenter(center)
        , radius(r)
    {
    }

    /**
    * 球体当たり判定の移動
    * 
    * @param[in] pos 移動座標
    */
    void Sphere::Move(const VECTOR& pos)
    {
        worldCenter = localCenter + pos;
    }

    /**
    * カプセル当たり判定のコンストラクタ
    */
    Capsule::Capsule()
        : localStart()
        , localEnd()
        , worldStart()
        , worldEnd()
        , radius(0.0f)
    {
    }

    /**
    * カプセル当たり判定のコンストラクタ
    * 
    * @param[in] startPos 始点初期座標
    * @param[in] endPos   終点初期座標
    * @param[in] r        半径
    */
    Capsule::Capsule(const VECTOR& startPos, const VECTOR& endPos, float r)
        : localStart(startPos)
        , localEnd(endPos)
        , worldStart(startPos)
        , worldEnd(endPos)
        , radius(r)
    {
    }

    /**
    * カプセル当たり判定の移動
    * 
    * @param[in] pos 移動座標
    */
    void Capsule::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    /**
    * 球体 対 球体 の当たり判定
    * 
    * @param[in] sphereA 球体A
    * @param[in] sphereB 球体B
    * @return    bool    衝突している場合はtrueを返す
    */
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB)
    {
        return HitCheck_Sphere_Sphere(sphereA.worldCenter, sphereA.radius, sphereB.worldCenter, sphereB.radius);
    }

    /**
    * 線分 対 球体 の当たり判定
    * 
    * @param[in] line   線分
    * @param[in] sphere 球体
    * @return    bool   衝突している場合はtrueを返す
    */
    bool CollisionPair(const LineSegment& line, const Sphere& sphere)
    {
        return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
    }

    /**
    * 球体 対 線分 の当たり判定
    * 
    * @param[in] sphere 球体
    * @parma[in] line   線分
    * @return    bool   衝突している場合はtrueを返す
    */
    bool CollisionPair(const Sphere& sphere, const LineSegment& line)
    {
        return CollisionPair(line, sphere);
    }

    /**
    * 球体 対 メッシュ の当たり判定
    * 
    * @param[in]  sphere        球体
    * @param[in]  modelHandle   メッシュのモデルID
    * @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
    * @return     bool          衝突している場合はtrueを返す
    */
    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.radius);
        if (collisionInfo.HitNum == 0)
        {
            return false;
        }
        return true;
    }

    /**
    * 線分 対 メッシュ の当たり判定
    * 
    * @param[in]  line          線分
    * @param[in]  modelHandle   メッシュのモデルID
    * @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
    * @return     bool          衝突している場合はtrueを返す
    */
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.worldStart, line.worldEnd);
        return collisionInfo.HitFlag;
    }

    /**
    * メッシュ 対 線分 の当たり判定
    * 
    * @param[in] modelHandel メッシュのモデルID
    * @param[in] line 線分
    * @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
    * @return bool 衝突している場合はtrueを返す
    * @detail 線分とメッシュの当たり判定関数の引数が反対になっている関数
    */
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        return CollisionPair(line, modelHandle, collisionInfo);
    }

    /**
    * 球体とメッシュとのめり込みを戻すベクトルを求める
    * 
    * @param[in]  sphere        球体
    * @param[out] collisionInfo MV1CollCheck_Sphere()関数が返す衝突情報
    * @return     VECTOR        球体がメッシュから離れる向きの移動ベクトルを返す
    */
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        /** 衝突球*/
        /** 球中心候補*/
        VECTOR moveCandidate = sphere.worldCenter;

        /** 球半径*/
        float radius = sphere.radius;

        /** ポリゴン平面法線*/
        VECTOR planeNormal;

        /** 移動ベクトル*/
        VECTOR moveVec = VGet(0, 0, 0);

        /** 移動量*/
        float moveLen = 0.0f;

        /** 移動候補*/
        VECTOR newCenter = sphere.worldCenter;

        /** 衝突ポリゴンをすべて回って、球のめり込みを解消する*/
        for (int i = 0; i < collisionInfo.HitNum; ++i)
        {
            /** 衝突ポリゴンの辺1*/
            VECTOR edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];

            /** 衝突ポリゴンの辺2*/
            VECTOR edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            /** 衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める*/
            planeNormal = VCross(edge1, edge2);
            planeNormal = VNorm(planeNormal);

            /** 球中心に最も近いポリゴン平面の点を求める*/
            VECTOR tmp = moveCandidate - collisionInfo.Dim[i].Position[0];
            float dot = VDot(planeNormal, tmp);

            /** 衝突点*/
            VECTOR hitPos = moveCandidate - planeNormal * dot;

            /** 球がどれくらいめり込んでいるかを算出*/
            VECTOR tmp2 = moveCandidate - hitPos;
            float len = VSize(tmp2);

            /** めり込んでいる場合は球の中心を押し戻し*/
            if (HitCheck_Sphere_Triangle(moveCandidate, radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                /** めり込み解消する位置まで移動*/
                len = radius - len;
                moveVec = planeNormal * len;
                moveCandidate += moveVec;
            }
        }

        /** 移動候補を移動位置にする*/
        newCenter = moveCandidate;

        /** 押し戻し量を返却*/
        return newCenter - sphere.worldCenter;
    }

}/** namespace My3dApp*/