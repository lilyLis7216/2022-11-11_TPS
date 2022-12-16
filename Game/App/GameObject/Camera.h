#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �J�����i�h���N���X�A�p�����F�Q�[���I�u�W�F�N�g�j
    /// </summary>
    class Camera : public GameObject
    {
    private:
        // �J�����̍��W
        //VECTOR pos;

        // �J�����̒��ړ_
        VECTOR lookPos;

        // �v���C���[����̑��Έʒu
        VECTOR cameraOffset;

        // �J�����̖ڕW�ʒu
        VECTOR aimCameraPos;

        // �J�����̒��ړ_�ڕW
        VECTOR aimLookPos;

        float speed;

        float yaw;

        float pitch;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="height">�J�����̍���</param>
        /// <param name="z"></param>
        Camera(float height, float z);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Camera();

        /// <summary>
        /// �J�����̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

    };
}// namespace My3dApp