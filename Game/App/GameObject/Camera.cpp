#include "Camera.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    // �J�����̂΂˂̒萔
    const float cameraSpringStrength = 2.0f;

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="height">�J�����̍���</param>
    /// <param name="z">�J�����̈���</param>
    Camera::Camera(float height, float z)
        : GameObject(ObjectTag::Camera)
        , lookPos()
        , aimCameraPos()
        , aimLookPos()
        , speed(0.03f)
        , pitch(0.5f)
        , yaw(3.1f)
    {
        pos = VGet(0, 0, 0);
        cameraOffset.x = 0;
        cameraOffset.y = height;
        cameraOffset.z = z;

        SetupCamera_Perspective(1000.0f);
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    Camera::~Camera()
    {
        // �����Ȃ�
    }

    /// <summary>
    /// �J�����̍X�V
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Camera::Update(float deltaTime)
    {
        // �J�����̒����ڕW�_�ƁA�J�����̈ʒu�ڕW�_���v�Z
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (player)
        {
            aimLookPos = player->GetPos();
            aimCameraPos = aimLookPos + cameraOffset;

            VECTOR lookMoveDir = aimLookPos - lookPos;
            VECTOR posMoveDir = aimCameraPos - pos;

            /*if (0 < GamePad::GetRightStickY() || CheckHitKey(KEY_INPUT_UP))
            {
                if (pitch < 1)
                {
                    pitch += speed;
                }
            }

            if (GamePad::GetRightStickY() < 0 || CheckHitKey(KEY_INPUT_DOWN))
            {
                if (pitch > 0)
                {
                    pitch -= speed;
                }
            }

            if (GamePad::GetRightStickX() < 0 || CheckHitKey(KEY_INPUT_LEFT))
            {
                yaw += speed;
            }

            if (0 < GamePad::GetRightStickX() || CheckHitKey(KEY_INPUT_RIGHT))
            {
                yaw -= speed;
            }

            pos.x = cameraOffset.y * cosf(yaw) * cosf(pitch) + player->GetPos().x + 100.0f;
            pos.y = cameraOffset.y * sinf(pitch) + player->GetPos().y;
            pos.z = cameraOffset.y * sinf(yaw) * cosf(pitch) + player->GetPos().z;*/

            lookPos += lookMoveDir * cameraSpringStrength * deltaTime;
            pos += posMoveDir * cameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(pos, lookPos);

            // DX���C�u�����̃J������Effekseer�̃J�����𓯊�
            Effekseer_Sync3DSetting();
        }
    }
}// namespace My3dApp