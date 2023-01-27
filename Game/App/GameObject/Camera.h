#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// カメラ（GameObject継承）
    /// </summary>
    class Camera : public GameObject
    {
    private:

        // カメラの注目点
        VECTOR lookPos;

        // プレイヤーからの相対位置
        VECTOR cameraOffset;

        // カメラの目標位置
        VECTOR aimCameraPos;

        // カメラの注目点目標
        VECTOR aimLookPos;

        float speed;

        float yaw;

        float pitch;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="height">カメラの高さ</param>
        /// <param name="z">カメラの引き</param>
        Camera(float height, float z);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Camera();

        /// <summary>
        /// カメラの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

    };
}// namespace My3dApp