#pragma once

#include <DxLib.h>

namespace My3dApp
{
    /** �x�N�g�����m�̉��Z*/
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

    /** �x�N�g�����m�̌��Z*/
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

    /** �x�N�g���̃X�J���{�i���萔�j*/
    VECTOR operator*(const float s, const VECTOR& rhs);

    /** �x�N�g���̃X�J���{�i�E�萔�j*/
    VECTOR operator*(const VECTOR& lhs, const float s);

    /** �x�N�g���̉��Z���*/
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

    /** �x�N�g���̌��Z���*/
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs);

    /** �x�N�g���̃X�J���{�i��Z����j*/
    VECTOR operator*=(VECTOR& lhs, const float s);

    /** 2�̃x�N�g���̊p�x���قړ������ǂ���*/
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2);

    /** nowVec����dirVec�̍ŒZ�̉�]�������v�Z����iY����]��z��j*/
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec);

    /** nowVec����aimVec�Ɍ�������degreeSpeed�̑��x��Y����]������*/
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed);

}/** namespace My3dApp*/