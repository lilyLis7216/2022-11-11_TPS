#pragma once

#include "DxLib.h"

namespace My3dApp
{
    /// <summary>
    /// ベクトル同士の加算
    /// </summary>
    /// <param name="lhs">1つ目のベクトル</param>
    /// <param name="rhs">2つ目のベクトル</param>
    /// <returns>加算後のベクトル</returns>
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトル同士の減算
    /// </summary>
    /// <param name="lhs">1つ目のベクトル</param>
    /// <param name="rhs">2つ目のベクトル</param>
    /// <returns>減算後のベクトル</returns>
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルのスカラ倍（左定数）
    /// </summary>
    /// <param name="s">定数</param>
    /// <param name="rhs">ベクトル</param>
    /// <returns>乗算後のベクトル</returns>
    VECTOR operator*(const float s, const VECTOR& rhs);

    /// <summary>
    /// ベクトルのスカラ倍（右定数）
    /// </summary>
    /// <param name="lhs">ベクトル</param>
    /// <param name="s">定数</param>
    /// <returns>乗算後のベクトル</returns>
    VECTOR operator*(const VECTOR& lhs, const float s);

    /// <summary>
    /// ベクトルの加算代入
    /// </summary>
    /// <param name="lhs">代入されるのベクトル</param>
    /// <param name="rhs">代入するベクトル</param>
    /// <returns>加算後のベクトル</returns>
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルの減算代入
    /// </summary>
    /// <param name="lhs">代入されるベクトル</param>
    /// <param name="rhs">代入するベクトル</param>
    /// <returns>減算後のベクトル</returns>
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルのスカラ倍（乗算代入）
    /// </summary>
    /// <param name="lhs">ベクトル</param>
    /// <param name="s">定数</param>
    /// <returns>乗算後のベクトル</returns>
    VECTOR operator*=(VECTOR& lhs, const float s);

    /// <summary>
    /// 2つのベクトルの角度がほぼ同じかどうか
    /// </summary>
    /// <param name="vec1">1つ目のベクトル</param>
    /// <param name="vec2">2つ目のベクトル</param>
    /// <returns>同じならtrue そうじゃなければfalse</returns>
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2);

    /// <summary>
    /// nowVecからdirVecの最短の回転方向を計算する（Y軸回転を想定）
    /// </summary>
    /// <param name="nowVec">現在の向きベクトル</param>
    /// <param name="dirVec">向きたい向きベクトル</param>
    /// <returns>時計回りなら1.0f 反時計回りなら-1.0f</returns>
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec);

    /// <summary>
    /// nowVecからaimVecに向かってdegreeSpeedの速度でY軸回転させる
    /// </summary>
    /// <param name="nowVec">現在の方向ベクトル</param>
    /// <param name="aimVec">目標方向ベクトル</param>
    /// <param name="degreeSpeed">速度</param>
    /// <returns></returns>
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed);

}// namespace My3dApp