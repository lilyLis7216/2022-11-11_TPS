#pragma once

#include <DxLib.h>

namespace My3dApp
{
    /** ベクトル同士の加算*/
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

    /** ベクトル同士の減算*/
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

    /** ベクトルのスカラ倍（左定数）*/
    VECTOR operator*(const float s, const VECTOR& rhs);

    /** ベクトルのスカラ倍（右定数）*/
    VECTOR operator*(const VECTOR& lhs, const float s);

    /** ベクトルの加算代入*/
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

    /** ベクトルの減算代入*/
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs);

    /** ベクトルのスカラ倍（乗算代入）*/
    VECTOR operator*=(VECTOR& lhs, const float s);

    /** 2つのベクトルの角度がほぼ同じかどうか*/
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2);

    /** nowVecからdirVecの最短の回転方向を計算する（Y軸回転を想定）*/
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec);

    /** nowVecからaimVecに向かってdegreeSpeedの速度でY軸回転させる*/
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed);

}/** namespace My3dApp*/