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

        const float selectSize = 1.0f;

        const float notSelectSize = 0.75f;

        int selectState;

        struct Star
        {
            int model;
            bool valid = false;
            float rotate = 0.0f;
            bool canRotate = true;
        };

        Star leftStar;

        Star middleStar;

        Star rightStar;

        Star aster;

        enum SelectState
        {
            BACK = 0,
            EXIT,
        };

        float nextStar;

        void StarUpdate(float deltaTime);

        float rotateCount;

        void MoveModel(float deltaTime);

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