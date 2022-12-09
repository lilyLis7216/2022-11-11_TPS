#include "Calc3D.h"

namespace My3dApp
{
    /**
    * ベクトル同士の加算
    * 
    * @param[in] lhs 1つ目のベクトル
    * @param[in] rhs 2つ目のベクトル
    * @return 加算後のベクトル
    */
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = lhs.x + rhs.x;
        retVec.y = lhs.y + rhs.y;
        retVec.z = lhs.z + rhs.z;
        return retVec;
    }

    /**
    * ベクトル同士の減算
    * 
    * @param[in] lhs 1つ目のベクトル
    * @param[in] rhs 2つ目のベクトル
    * @return 減算後のベクトル
    */
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = lhs.x - rhs.x;
        retVec.y = lhs.y - rhs.y;
        retVec.z = lhs.z - rhs.z;
        return retVec;
    }

    /**
    * ベクトルのスカラ倍（左定数）
    * 
    * @param[in] s   定数
    * @param[in] rhs ベクトル
    * @return 乗算後のベクトル
    */
    VECTOR operator*(const float s, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = s * rhs.x;
        retVec.y = s * rhs.y;
        retVec.z = s * rhs.z;
        return retVec;
    }

    /**
    * ベクトルのスカラ倍（右定数）
    * 
    * @param[in] lhs ベクトル
    * @param[in] s   定数
    * @return 乗算後のベクトル
    */
    VECTOR operator*(const VECTOR& lhs, const float s)
    {
        VECTOR retVec;
        retVec.x = lhs.x * s;
        retVec.y = lhs.y * s;
        retVec.z = lhs.z * s;
        return retVec;
    }

    /**
    * ベクトルの加算代入
    * 
    * @param[out] lhs 代入されるのベクトル
    * @param[in]  rhs 代入するベクトル
    * @return 加算後ノベクトル
    */
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    /**
    * ベクトルの減算代入
    * 
    * @param[out] lhs 代入されるベクトル
    * @param[in]  rhs 代入するベクトル
    * @return 減算後ノベクトル
    */
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    /**
    * ベクトルのスカラ倍（乗算代入）
    * 
    * @param[out] lhs ベクトル
    * @param[in]  s   定数
    * @return 乗算後ノベクトル
    */
    VECTOR operator*=(VECTOR& lhs, const float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    /** 
    * 2つのベクトルの角度がほぼ同じかどうか
    * 
    * @param[in] vec1 1つ目のベクトル
    * @param[in] vec2 2つ目のベクトル
    * @return 同じならtrue そうじゃなければfalse
    */
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2)
    {
        float ret = VDot(vec1, vec2);

        /** 内積が1なら同じ角度なので*/
        if (ret > 0.99f)
        {
            return true;
        }
        return false;
    }

    /**
    * nowVecからdirVecの最短の回転方向を計算する（Y軸回転を想定）
    * 
    * @param[in] nowVec 現在の向きベクトル
    * @param[in] dir    向きたい向きベクトル
    * @return 時計回りなら1.0f 反時計回りなら-1.0f
    */
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec)
    {
        VECTOR axis;
        axis = VCross(nowVec, dirVec);

        /** 反時計回りなら*/
        if (axis.y < 0.0f)
        {
            return -1.0f;
        }
        /** 時計回り*/
        return 1.0f;
    }

    /**
    * nowVecからaimVecに向かってdegreeSpeedの速度でY軸回転させる
    * 
    * @param[in] nowVec      現在の方向ベクトル
    * @param[in] aimVec      目標方向ベクトル
    * @param[in] degreeSpeed 速度
    */
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed)
    {
        /** 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる*/
        float rotRadian = (DX_PI_F * degreeSpeed / 180.0f);
        rotRadian *= CalcRotationDirectionYAXis(nowVec, aimVec);

        /** y軸回転行列の作成*/
        MATRIX yRotMat = MGetRotY(rotRadian);

        /** y軸回転をする*/
        VECTOR rotVec;
        rotVec = VTransform(nowVec, yRotMat);

        return rotVec;
    }
}/** namespace My3dApp*/