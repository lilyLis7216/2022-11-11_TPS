#pragma once 

#include "BaseEnemy.h"

namespace My3dApp
{
    /// <summary>
    /// ノーマルエネミークラス（BaseEnemy継承）
    /// </summary>
    class NormalEnemy : public BaseEnemy
    {
    private:
        /// <summary>
        /// ノーマルエネミーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime) override;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos"></param>
        NormalEnemy( VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~NormalEnemy();
        
        /// <summary>
        /// ノーマルエネミーの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;
    };
}// namespace My3dApp