#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// �x�N�g�����m�̉��Z
    /// </summary>
    /// <param name="lhs">1�ڂ̃x�N�g��</param>
    /// <param name="rhs">2�ڂ̃x�N�g��</param>
    /// <returns>���Z��̃x�N�g��</returns>
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// �x�N�g�����m�̌��Z
    /// </summary>
    /// <param name="lhs">1�ڂ̃x�N�g��</param>
    /// <param name="rhs">2�ڂ̃x�N�g��</param>
    /// <returns>���Z��̃x�N�g��</returns>
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// �x�N�g���̃X�J���{�i���萔�j
    /// </summary>
    /// <param name="s">�萔</param>
    /// <param name="rhs">�x�N�g��</param>
    /// <returns>��Z��̃x�N�g��</returns>
    VECTOR operator*(const float s, const VECTOR& rhs);

    /// <summary>
    /// �x�N�g���̃X�J���{�i�E�萔�j
    /// </summary>
    /// <param name="lhs">�x�N�g��</param>
    /// <param name="s">�萔</param>
    /// <returns>��Z��̃x�N�g��</returns>
    VECTOR operator*(const VECTOR& lhs, const float s);

    /// <summary>
    /// �x�N�g���̉��Z���
    /// </summary>
    /// <param name="lhs">��������̃x�N�g��</param>
    /// <param name="rhs">�������x�N�g��</param>
    /// <returns>���Z��̃x�N�g��</returns>
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// �x�N�g���̌��Z���
    /// </summary>
    /// <param name="lhs">��������x�N�g��</param>
    /// <param name="rhs">�������x�N�g��</param>
    /// <returns>���Z��̃x�N�g��</returns>
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// �x�N�g���̃X�J���{�i��Z����j
    /// </summary>
    /// <param name="lhs">�x�N�g��</param>
    /// <param name="s">�萔</param>
    /// <returns>��Z��̃x�N�g��</returns>
    VECTOR operator*=(VECTOR& lhs, const float s);

    /// <summary>
    /// 2�̃x�N�g���̊p�x���قړ������ǂ���
    /// </summary>
    /// <param name="vec1">1�ڂ̃x�N�g��</param>
    /// <param name="vec2">2�ڂ̃x�N�g��</param>
    /// <returns>�����Ȃ�true ��������Ȃ����false</returns>
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2);

    /// <summary>
    /// nowVec����dirVec�̍ŒZ�̉�]�������v�Z����iY����]��z��j
    /// </summary>
    /// <param name="nowVec">���݂̌����x�N�g��</param>
    /// <param name="dirVec">�������������x�N�g��</param>
    /// <returns>���v���Ȃ�1.0f �����v���Ȃ�-1.0f</returns>
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec);

    /// <summary>
    /// nowVec����aimVec�Ɍ�������degreeSpeed�̑��x��Y����]������
    /// </summary>
    /// <param name="nowVec">���݂̕����x�N�g��</param>
    /// <param name="aimVec">�ڕW�����x�N�g��</param>
    /// <param name="degreeSpeed">���x</param>
    /// <returns></returns>
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed);

}// namespace My3dApp