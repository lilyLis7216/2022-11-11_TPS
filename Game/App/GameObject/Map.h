#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// マップ（派生クラス、継承元：ゲームオブジェクト）
    /// </summary>
    class Map : public GameObject
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        Map(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Map();

        /// <summary>
        /// マップの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// マップの描画
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp