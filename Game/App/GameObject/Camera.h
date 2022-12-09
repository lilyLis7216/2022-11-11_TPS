#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Camera : public GameObject
    {
    private:
        /** �J�����̍��W*/
        VECTOR pos;

        /** �J�����̒��ړ_*/
        VECTOR lookPos;

        /** �v���C���[����̑��Έʒu*/
        VECTOR cameraOffset;

        /** �J�����ڕW�ʒu*/
        VECTOR aimCameraPos;

        /** �J�������ړ_�ڕW*/
        VECTOR aimLookPos;

    public:
        /** �R���X�g���N�^*/
        Camera(float height, float z);

        /** �f�X�g���N�^*/
        ~Camera();

        void Update(float deltaTime) override;
    };
}/** namespace My3dApp*/