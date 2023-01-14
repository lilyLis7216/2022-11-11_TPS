#include "Camera.h"
#include "ObjectTag.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    // カメラのばねの定数
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
        // 処理なし
    }

    void Camera::Update(float deltaTime)
    {
        // カメラの注視目標点と、カメラの位置目標点を計算
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (player)
        {
            aimLookPos = player->GetPos();
            aimCameraPos = aimLookPos + cameraOffset;

            VECTOR lookMoveDir = aimLookPos - lookPos;
            VECTOR posMoveDir = aimCameraPos - pos;

            lookPos += lookMoveDir * cameraSpringStrength * deltaTime;
            pos += posMoveDir * cameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(pos, lookPos);
        }
    }
}// namespace My3dApp