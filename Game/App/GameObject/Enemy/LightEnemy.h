#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// ライトエネミークラス（BaseEnemy継承）
    /// </summary>
    class LightEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// ライトエネミーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime)override;

        void Shot(float deltaTime) override;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        LightEnemy(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </symmary>
        ~LightEnemy();

        /// <summary>
        /// ライトエネミーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp