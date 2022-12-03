#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /**
    * ���������蔻��
    */
    struct LineSegment
    {
        /** */
        LineSegment();

        /** */
        LineSegment(const VECTOR& startPos, const VECTOR& endPos);

        /** ���������蔻��̈ړ�*/
        void Move(const VECTOR& pos);

        /** �����̃��[�J���n�_���W*/
        VECTOR localStart;

        /** �����̃��[�J���I�_���W*/
        VECTOR localEnd;

        /** �����̃��[���h�n�_���W*/
        VECTOR worldStart;

        /** �����̃��[���h�I�_���W*/
        VECTOR worldEnd;
    };

    /**
    * ���̓����蔻��
    */
    struct Sphere
    {
        /** */
        Sphere();

        /** */
        Sphere(const VECTOR& center, float r);

        /** ���̓����蔻��̈ړ�*/
        void Move(const VECTOR& pos);

        /** ���̂̃��[�J�����S���W*/
        VECTOR localCenter;

        /** ���̂̃��[���h���S���W*/
        VECTOR worldCenter;

        /** ���̂̔��a*/
        float radius;
    };

    /**
    * �J�v�Z�������蔻��
    */
    struct Capsule
    {
        /** */
        Capsule();

        /** */
        Capsule(const VECTOR& start, const VECTOR& end, float r);

        /** �J�v�Z�������蔻��̈ړ�*/
        void Move(const VECTOR& pos);

        /** �J�v�Z���̃��[�J���n�_���W*/
        VECTOR localStart;

        /** �J�v�Z���̃��[�J���I�_���W*/
        VECTOR localEnd;

        /** �J�v�Z���̃��[���h�n�_���W*/
        VECTOR worldStart;

        /** �J�v�Z���̃��[���h�I�_���W*/
        VECTOR worldEnd;

        /** �J�v�Z���̔��a*/
        float radius;
    };

    /** ���̑΋��̂̓����蔻��*/
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB);

    /** �����΋��̂̓����蔻��*/
    bool CollisionPair(const LineSegment& line, const Sphere& sphere);

    /** ���̑ΐ����̓����蔻��*/
    bool CollisionPair(const Sphere& sphere, const LineSegment& line);

    /** ���̑΃��b�V���̓����蔻��*/
    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);

    /** �����΃��b�V���̓����蔻��*/
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

    /** ���b�V���ΐ����̓����蔻��*/
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo);

    /** ���̂ƃ��b�V���Ƃ̔����̉����߂��ʌv�Z*/
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);

}/** namespace My3dApp*/