#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Camera : public GameObject
    {
    private:
        /** カメラの座標*/
        VECTOR pos;

        /** カメラの注目点*/
        VECTOR lookPos;

        /** プレイヤーからの相対位置*/
        VECTOR cameraOffset;

        /** カメラ目標位置*/
        VECTOR aimCameraPos;

        /** カメラ注目点目標*/
        VECTOR aimLookPos;

    public:
        /** コンストラクタ*/
        Camera(float height, float z);

        /** デストラクタ*/
        ~Camera();

        void Update(float deltaTime) override;
    };
}/** namespace My3dApp*/