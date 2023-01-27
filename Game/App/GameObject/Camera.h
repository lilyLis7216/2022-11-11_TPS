#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �J�����iGameObject�p���j
    /// </summary>
    class Camera : public GameObject
    {
    private:

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
        /// <param name="z">�J�����̈���</param>
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