#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// タイトルシーン（派生クラス、継承元：シーンベース）
    /// </summary>
    class Title : public SceneBase
    {
    private:
        int titleModel;

        int startModel;

        int exitModel;

        float rotateCount;

        void MoveModel(float deltaTime);

        int selectState;

        enum SelectState
        {
            START = 0,
            EXIT,
        };

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Title();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Title();

        /// <summary>
        /// タイトルシーンの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// タイトルシーンの描画
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp