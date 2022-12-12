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
        // �Փˋ�
        // �����S���
        VECTOR moveCandidate = sphere.worldCenter;

        // �����a
        float radius = sphere.radius;

        // �|���S�����ʖ@��
        VECTOR planeNormal;

        // �ړ��x�N�g��
        VECTOR moveVec = VGet(0, 0, 0);

        // �ړ���
        float moveLen = 0.0f;

        // �ړ����
        VECTOR newCenter = sphere.worldCenter;

        // �Փ˃|���S�������ׂĉ���āA���̂߂荞�݂���������
        for (int i = 0; i < collisionInfo.HitNum; ++i)
        {
            // �Փ˃|���S���̕�1
            VECTOR edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];

            // �Փ˃|���S���̕�2
            VECTOR edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            // �Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
            planeNormal = VCross(edge1, edge2);
            planeNormal = VNorm(planeNormal);

            // �����S�ɍł��߂��|���S�����ʂ̓_�����߂�
            VECTOR tmp = moveCandidate - collisionInfo.Dim[i].Position[0];
            float dot = VDot(planeNormal, tmp);

            // �Փ˓_
            VECTOR hitPos = moveCandidate - planeNormal * dot;

            // �����ǂꂭ�炢�߂荞��ł��邩���Z�o
            VECTOR tmp2 = moveCandidate - hitPos;
            float len = VSize(tmp2);

            // �߂荞��ł���ꍇ�͋��̒��S�������߂�
            if (HitCheck_Sphere_Triangle(moveCandidate, radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                // �߂荞�݉�������ʒu�܂ňړ�
                len = radius - len;
                moveVec = planeNormal * len;
                moveCandidate += moveVec;
            }
        }

        // �ړ������ړ��ʒu�ɂ���
        newCenter = moveCandidate;

        // �����߂��ʂ�ԋp
        return newCenter - sphere.worldCenter;
    }
}// namespace My3dApp