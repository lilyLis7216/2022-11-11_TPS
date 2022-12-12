#include "Calc3D.h"

namespace My3dApp
{
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = lhs.x + rhs.x;
        retVec.y = lhs.y + rhs.y;
        retVec.z = lhs.z + rhs.z;
        return retVec;
    }

    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = lhs.x - rhs.x;
        retVec.y = lhs.y - rhs.y;
        retVec.z = lhs.z - rhs.z;
        return retVec;
    }

    VECTOR operator*(const float s, const VECTOR& rhs)
    {
        VECTOR retVec;
        retVec.x = s * rhs.x;
        retVec.y = s * rhs.y;
        retVec.z = s * rhs.z;
        return retVec;
    }

    VECTOR operator*(const VECTOR& lhs, const float s)
    {
        VECTOR retVec;
        retVec.x = lhs.x * s;
        retVec.y = lhs.y * s;
        retVec.z = lhs.z * s;
        return retVec;
    }

    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    VECTOR operator*=(VECTOR& lhs, const float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2)
    {
        float ret = VDot(vec1, vec2);

        // 内積が1なら同じ角度なので
        if (ret > 0.99f)
        {
            return true;
        }
        return false;
    }

    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec)
    {
        VECTOR axis;
        axis = VCross(nowVec, dirVec);

        // 反時計回りなら
        if (axis.y < 0.0f)
        {
            return -1.0f;
        }
        // 時計回り
        return 1.0f;
    }

    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed)
    {
        // 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
        float rotRadian = (DX_PI_F * degreeSpeed / 180.0f);
        rotRadian *= CalcRotationDirectionYAXis(nowVec, aimVec);

        // y軸回転行列の作成
        MATRIX yRotMat = MGetRotY(rotRadian);

        // y軸回転をする
        VECTOR rotVec;
        rotVec = VTransform(nowVec, yRotMat);

        return rotVec;
    }
}// namespace My3dApp