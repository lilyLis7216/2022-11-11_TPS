#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// プレイシーン（派生クラス、継承元：シーンベース）
    /// </summary>
    class Play : public SceneBase
    {
    private:

        // タイマー
        float timer;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Play();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Play();

        /// <summary>
        /// プレイシーンの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// プレイシーンの描画
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp