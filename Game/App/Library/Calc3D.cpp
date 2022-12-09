#include "Calc3D.h"

namespace My3dApp
{
    /**
    * �x�N�g�����m�̉��Z
    * 
    * @param[in] lhs 1�ڂ̃x�N�g��
    * @param[in] rhs 2�ڂ̃x�N�g��
    * @return ���Z��̃x�N�g��
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
    * �x�N�g�����m�̌��Z
    * 
    * @param[in] lhs 1�ڂ̃x�N�g��
    * @param[in] rhs 2�ڂ̃x�N�g��
    * @return ���Z��̃x�N�g��
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
    * �x�N�g���̃X�J���{�i���萔�j
    * 
    * @param[in] s   �萔
    * @param[in] rhs �x�N�g��
    * @return ��Z��̃x�N�g��
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
    * �x�N�g���̃X�J���{�i�E�萔�j
    * 
    * @param[in] lhs �x�N�g��
    * @param[in] s   �萔
    * @return ��Z��̃x�N�g��
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
    * �x�N�g���̉��Z���
    * 
    * @param[out] lhs ��������̃x�N�g��
    * @param[in]  rhs �������x�N�g��
    * @return ���Z��m�x�N�g��
    */
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    /**
    * �x�N�g���̌��Z���
    * 
    * @param[out] lhs ��������x�N�g��
    * @param[in]  rhs �������x�N�g��
    * @return ���Z��m�x�N�g��
    */
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    /**
    * �x�N�g���̃X�J���{�i��Z����j
    * 
    * @param[out] lhs �x�N�g��
    * @param[in]  s   �萔
    * @return ��Z��m�x�N�g��
    */
    VECTOR operator*=(VECTOR& lhs, const float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    /** 
    * 2�̃x�N�g���̊p�x���قړ������ǂ���
    * 
    * @param[in] vec1 1�ڂ̃x�N�g��
    * @param[in] vec2 2�ڂ̃x�N�g��
    * @return �����Ȃ�true ��������Ȃ����false
    */
    bool IsNearAngle(const VECTOR& vec1, const VECTOR& vec2)
    {
        float ret = VDot(vec1, vec2);

        /** ���ς�1�Ȃ瓯���p�x�Ȃ̂�*/
        if (ret > 0.99f)
        {
            return true;
        }
        return false;
    }

    /**
    * nowVec����dirVec�̍ŒZ�̉�]�������v�Z����iY����]��z��j
    * 
    * @param[in] nowVec ���݂̌����x�N�g��
    * @param[in] dir    �������������x�N�g��
    * @return ���v���Ȃ�1.0f �����v���Ȃ�-1.0f
    */
    float CalcRotationDirectionYAXis(const VECTOR& nowVec, const VECTOR& dirVec)
    {
        VECTOR axis;
        axis = VCross(nowVec, dirVec);

        /** �����v���Ȃ�*/
        if (axis.y < 0.0f)
        {
            return -1.0f;
        }
        /** ���v���*/
        return 1.0f;
    }

    /**
    * nowVec����aimVec�Ɍ�������degreeSpeed�̑��x��Y����]������
    * 
    * @param[in] nowVec      ���݂̕����x�N�g��
    * @param[in] aimVec      �ڕW�����x�N�g��
    * @param[in] degreeSpeed ���x
    */
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeSpeed)
    {
        /** �p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�*/
        float rotRadian = (DX_PI_F * degreeSpeed / 180.0f);
        rotRadian *= CalcRotationDirectionYAXis(nowVec, aimVec);

        /** y����]�s��̍쐬*/
        MATRIX yRotMat = MGetRotY(rotRadian);

        /** y����]������*/
        VECTOR rotVec;
        rotVec = VTransform(nowVec, yRotMat);

        return rotVec;
    }
}/** namespace My3dApp*/