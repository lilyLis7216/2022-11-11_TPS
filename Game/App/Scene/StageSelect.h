#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// ステージセレクトシーン（派生クラス、継承元：シーンベース）
    /// </summary>
    class StageSelect : public SceneBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        StageSelect();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~StageSelect();

        /** ステージセレクトの更新*/

        /// <summary>
        /// ステージセレクトシーンの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// ステージセレクトシーンの描画
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp