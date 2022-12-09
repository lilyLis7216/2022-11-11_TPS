#include "Camera.h"
#include "ObjectTag.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"

namespace My3dApp
{
    /** ƒJƒƒ‰‚Ì‚Î‚Ë’è”*/
    const float cameraSpringStrength = 2.0f;

    Camera::Camera(float height, float z)
        : GameObject(ObjectTag::Camera)
        , pos()
        , lookPos()
        , aimCameraPos()
        , aimLookPos()
    {
        cameraOffset.x = 0;
        cameraOffset.y = height;
        cameraOffset.z = z;
    }

    Camera::~Camera()
    {
        /** ˆ—‚È‚µ*/
    }

    void Camera::Update(float deltaTime)
    {
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
}/** namespace My3dApp*/