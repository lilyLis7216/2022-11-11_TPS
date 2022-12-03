#include "Collision.h"
#include "Calc3D.h"

namespace My3dApp
{
    /**
    * ���������蔻��̃R���X�g���N�^
    */
    LineSegment::LineSegment()
        : localStart()
        , localEnd()
        , worldStart()
        , worldEnd()
    {
    }

    /**
    * ���������蔻��̃R���X�g���N�^
    * 
    * @param[in] startPos �n�_�������W
    * @param[in] endPos   �I�_�������W
    */
    LineSegment::LineSegment(const VECTOR& startPos, const VECTOR& endPos)
        : localStart(startPos)
        , localEnd(endPos)
        , worldStart(startPos)
        , worldEnd(endPos)
    {
    }

    /**
    * ���������蔻��̈ړ�
    * 
    * @param[in] pos �ړ����W
    */
    void LineSegment::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    /**
    * ���̓����蔻��̃R���X�g���N�^
    */
    Sphere::Sphere()
        : localCenter()
        , worldCenter()
        , radius(0.0f)
    {
    }

    /**
    * ���̓����蔻��̃R���X�g���N�^
    * 
    * @param[in] center ���S���W
    * @param[in] r      ���a
    */
    Sphere::Sphere(const VECTOR& center, float r)
        : localCenter(center)
        , worldCenter(center)
        , radius(r)
    {
    }

    /**
    * ���̓����蔻��̈ړ�
    * 
    * @param[in] pos �ړ����W
    */
    void Sphere::Move(const VECTOR& pos)
    {
        worldCenter = localCenter + pos;
    }

    /**
    * �J�v�Z�������蔻��̃R���X�g���N�^
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
    * �J�v�Z�������蔻��̃R���X�g���N�^
    * 
    * @param[in] startPos �n�_�������W
    * @param[in] endPos   �I�_�������W
    * @param[in] r        ���a
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
    * �J�v�Z�������蔻��̈ړ�
    * 
    * @param[in] pos �ړ����W
    */
    void Capsule::Move(const VECTOR& pos)
    {
        worldStart = localStart + pos;
        worldEnd = localEnd + pos;
    }

    /**
    * ���� �� ���� �̓����蔻��
    * 
    * @param[in] sphereA ����A
    * @param[in] sphereB ����B
    * @return    bool    �Փ˂��Ă���ꍇ��true��Ԃ�
    */
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB)
    {
        return HitCheck_Sphere_Sphere(sphereA.worldCenter, sphereA.radius, sphereB.worldCenter, sphereB.radius);
    }

    /**
    * ���� �� ���� �̓����蔻��
    * 
    * @param[in] line   ����
    * @param[in] sphere ����
    * @return    bool   �Փ˂��Ă���ꍇ��true��Ԃ�
    */
    bool CollisionPair(const LineSegment& line, const Sphere& sphere)
    {
        return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
    }

    /**
    * ���� �� ���� �̓����蔻��
    * 
    * @param[in] sphere ����
    * @parma[in] line   ����
    * @return    bool   �Փ˂��Ă���ꍇ��true��Ԃ�
    */
    bool CollisionPair(const Sphere& sphere, const LineSegment& line)
    {
        return CollisionPair(line, sphere);
    }

    /**
    * ���� �� ���b�V�� �̓����蔻��
    * 
    * @param[in]  sphere        ����
    * @param[in]  modelHandle   ���b�V���̃��f��ID
    * @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
    * @return     bool          �Փ˂��Ă���ꍇ��true��Ԃ�
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
    * ���� �� ���b�V�� �̓����蔻��
    * 
    * @param[in]  line          ����
    * @param[in]  modelHandle   ���b�V���̃��f��ID
    * @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
    * @return     bool          �Փ˂��Ă���ꍇ��true��Ԃ�
    */
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.worldStart, line.worldEnd);
        return collisionInfo.HitFlag;
    }

    /**
    * ���b�V�� �� ���� �̓����蔻��
    * 
    * @param[in] modelHandel ���b�V���̃��f��ID
    * @param[in] line ����
    * @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
    * @return bool �Փ˂��Ă���ꍇ��true��Ԃ�
    * @detail �����ƃ��b�V���̓����蔻��֐��̈��������΂ɂȂ��Ă���֐�
    */
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        return CollisionPair(line, modelHandle, collisionInfo);
    }

    /**
    * ���̂ƃ��b�V���Ƃ̂߂荞�݂�߂��x�N�g�������߂�
    * 
    * @param[in]  sphere        ����
    * @param[out] collisionInfo MV1CollCheck_Sphere()�֐����Ԃ��Փˏ��
    * @return     VECTOR        ���̂����b�V�����痣�������̈ړ��x�N�g����Ԃ�
    */
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        /** �Փˋ�*/
        /** �����S���*/
        VECTOR moveCandidate = sphere.worldCenter;

        /** �����a*/
        float radius = sphere.radius;

        /** �|���S�����ʖ@��*/
        VECTOR planeNormal;

        /** �ړ��x�N�g��*/
        VECTOR moveVec = VGet(0, 0, 0);

        /** �ړ���*/
        float moveLen = 0.0f;

        /** �ړ����*/
        VECTOR newCenter = sphere.worldCenter;

        /** �Փ˃|���S�������ׂĉ���āA���̂߂荞�݂���������*/
        for (int i = 0; i < collisionInfo.HitNum; ++i)
        {
            /** �Փ˃|���S���̕�1*/
            VECTOR edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];

            /** �Փ˃|���S���̕�2*/
            VECTOR edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            /** �Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�*/
            planeNormal = VCross(edge1, edge2);
            planeNormal = VNorm(planeNormal);

            /** �����S�ɍł��߂��|���S�����ʂ̓_�����߂�*/
            VECTOR tmp = moveCandidate - collisionInfo.Dim[i].Position[0];
            float dot = VDot(planeNormal, tmp);

            /** �Փ˓_*/
            VECTOR hitPos = moveCandidate - planeNormal * dot;

            /** �����ǂꂭ�炢�߂荞��ł��邩���Z�o*/
            VECTOR tmp2 = moveCandidate - hitPos;
            float len = VSize(tmp2);

            /** �߂荞��ł���ꍇ�͋��̒��S�������߂�*/
            if (HitCheck_Sphere_Triangle(moveCandidate, radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                /** �߂荞�݉�������ʒu�܂ňړ�*/
                len = radius - len;
                moveVec = planeNormal * len;
                moveCandidate += moveVec;
            }
        }

        /** �ړ������ړ��ʒu�ɂ���*/
        newCenter = moveCandidate;

        /** �����߂��ʂ�ԋp*/
        return newCenter - sphere.worldCenter;
    }

}/** namespace My3dApp*/