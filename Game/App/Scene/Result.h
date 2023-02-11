#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// リザルトシーン（派生クラス、継承元：シーンベース）
    /// </summary>
    class Result : public SceneBase
    {
    private:
        int resultModel;

        int backModel;

        int exitModel;

        int middleStar;

        int leftStar;

        int rightStar;

        const float selectSize = 1.0f;

        const float notSelectSize = 0.75f;

        int selectState;

        enum SelectState
        {
            BACK = 0,
            EXIT,
        };

        float nextStar;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Result();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Result();

        /// <summary>
        /// リザルトシーンの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// リザルトシーンの描画
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp