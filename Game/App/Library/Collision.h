#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// ���������蔻��
    /// </summary>
    struct LineSegment
    {
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        LineSegment();

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="startPos">�����n�_���W</param>
        /// <param name="endPos">�����I�_���W</param>
        LineSegment(const VECTOR& startPos, const VECTOR& endPos);

        /** ���������蔻��̈ړ�*/

        /// <summary>
        /// ���������蔻��̈ړ�
        /// </summary>
        /// <param name="pos">�ړ����W</param>
        void Move(const VECTOR& pos);

        // �����̃��[�J���n�_���W
        VECTOR localStart;

        // �����̃��[�J���I�_���W
        VECTOR localEnd;

        // �����̃��[���h�n�_���W
        VECTOR worldStart;

        // �����̃��[���h�I�_���W
        VECTOR worldEnd;

    };

    /// <summary>
    /// ���̓����蔻��
    /// </summary>
    struct Sphere
    {
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Sphere();

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="center">���S���W</param>
        /// <param name="r">���a</param>
        Sphere(const VECTOR& center, float r);

        /// <summary>
        /// ���̓����蔻��̈ړ�
        /// </summary>
        /// <param name="pos">�ړ����W</param>
        void Move(const VECTOR& pos);

        // ���̂̃��[�J�����S���W
        VECTOR localCenter;

        // ���̂̃��[���h���S���W
        VECTOR worldCenter;

        // ���̂̔��a
        float radius;

    };

    /// <summary>
    /// �J�v�Z�������蔻��
    /// </summary>
    struct Capsule
    {
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Capsule();

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="start">�����n�_���W</param>
        /// <param name="end">�����I�_���W</param>
        /// <param name="r">���a</param>
        Capsule(const VECTOR& start, const VECTOR& end, float r);

        /// <summary>
        /// �J�v�Z�������蔻��̈ړ�
        /// </summary>
        /// <param name="pos">�ړ����W</param>
        void Move(const VECTOR& pos);

        // �J�v�Z���̃��[�J���n�_���W
        VECTOR localStart;

        // �J�v�Z���̃��[�J���I�_���W
        VECTOR localEnd;

        // �J�v�Z���̃��[���h�n�_���W
        VECTOR worldStart;

        // �J�v�Z���̃��[���h�I�_���W
        VECTOR worldEnd;

        // �J�v�Z���̔��a
        float radius;

    };

    /// <summary>
    /// ���̑΋��̂̓����蔻��
    /// </summary>
    /// <param name="sphereA">����A</param>
    /// <param name="sphereB">����B</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const Sphere& sphereA, const Sphere& sphereB);

    /// <summary>
    /// �����΋��̂̓����蔻��
    /// </summary>
    /// <param name="line">����</param>
    /// <param name="sphere">����</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const LineSegment& line, const Sphere& sphere);

    /// <summary>
    /// ���̑ΐ����̓����蔻��
    /// </summary>
    /// <param name="sphere">����</param>
    /// <param name="line">����</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const Sphere& sphere, const LineSegment& line);

    /// <summary>
    /// ���� �� ���b�V�� �̓����蔻��
    /// </summary>
    /// <param name="sphere">����</param>
    /// <param name="modelHandle">���b�V���̃��f��ID</param>
    /// <param name="collisionInfo">���������ꍇ�̃|���S�����A�|���S�����X�g</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);

    /// <summary>
    /// �����΃��b�V���̓����蔻��
    /// </summary>
    /// <param name="line">����</param>
    /// <param name="modelHandle">���b�V���̃��f��ID</param>
    /// <param name="collisionInfo">���������ꍇ�̃|���S�����A�|���S�����X�g</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

    /// <summary>
    /// ���b�V���ΐ����̓����蔻��
    /// </summary>
    /// <param name="modelHandle">���b�V���̃��f��ID</param>
    /// <param name="line">����</param>
    /// <param name="collisionInfo">���������ꍇ�̃|���S�����A�|���S�����X�g</param>
    /// <returns>�Փ˂��Ă���ꍇ��true��Ԃ�</returns>
    bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo);

    /// <summary>
    /// ���̂ƃ��b�V���Ƃ̔����̉����߂��ʌv�Z
    /// </summary>
    /// <param name="sphere">����</param>
    /// <param name="collisionInfo">MV1CollCheck_Sphere()�֐����Ԃ��Փˏ��</param>
    /// <returns>���̂����b�V�����痣�������̈ړ��x�N�g����Ԃ�</returns>
    VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);

}// namespace My3dApp