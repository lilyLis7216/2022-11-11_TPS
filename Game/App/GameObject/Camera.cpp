#include "Camera.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    // カメラのばねの定数
    const float cameraSpringStrength = 2.0f;

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="height">カメラの高さ</param>
    /// <param name="z">カメラの引き</param>
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
    /// デストラクタ
    /// </summary>
    Camera::~Camera()
    {
        // 処理なし
    }

    /// <summary>
    /// カメラの更新
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
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

            // DXライブラリのカメラとEffekseerのカメラを同期
            Effekseer_Sync3DSetting();
        }
    }
}// namespace My3dApp