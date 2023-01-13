#include "Camera.h"
#include "ObjectTag.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    // �J�����̂΂˂̒萔
    const float cameraSpringStrength = 2.0f;

    Camera::Camera(float height, float z)
        : GameObject(ObjectTag::Camera)
        //, pos(initPos)
        , lookPos()
        , aimCameraPos()
        , aimLookPos()
        , speed(0.03f)
        , pitch(0.5f)
        , yaw(3.1f)
    {
        pos = initPos;
        cameraOffset.x = 0;
        cameraOffset.y = height;
        cameraOffset.z = z;
    }

    Camera::~Camera()
    {
        // �����Ȃ�
    }

    void Camera::Update(float deltaTime)
    {
        // �J�����̒����ڕW�_�ƁA�J�����̈ʒu�ڕW�_���v�Z
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (player)
        {
            aimLookPos = player->GetPos();
            aimCameraPos = aimLookPos + cameraOffset;

            // �J�����ʒu����ڕW�_�Ɍ������x�N�g�����v�Z
            VECTOR lookMoveDir = aimLookPos - lookPos;
            VECTOR posMoveDir = aimCameraPos - pos;

            // ��
            if (0 < GamePad::GetRightStickY() || CheckHitKey(KEY_INPUT_UP))
            {
                if (pitch < 1)
                {
                    pitch += speed;
                }
            }

            // ��
            if (GamePad::GetRightStickY() < 0 || CheckHitKey(KEY_INPUT_DOWN))
            {
                if (pitch > 0)
                {
                    pitch -= speed;
                }
            }

            // ��
            if (GamePad::GetRightStickX() < 0 || CheckHitKey(KEY_INPUT_LEFT))
            {
                yaw += speed;
            }

            // �E
            if (0 < GamePad::GetRightStickX() || CheckHitKey(KEY_INPUT_RIGHT))
            {
                yaw -= speed;
            }

            pos.x = cameraOffset.y * cosf(yaw) * cosf(pitch) + player->GetPos().x + 100.0f;
            pos.y = cameraOffset.y * sinf(pitch) + player->GetPos().y;
            pos.z = cameraOffset.y * sinf(yaw) * cosf(pitch) + player->GetPos().z;

            lookPos += lookMoveDir * cameraSpringStrength * deltaTime;
            pos += posMoveDir * cameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(pos, lookPos);
        }
    }
}// namespace My3dApp