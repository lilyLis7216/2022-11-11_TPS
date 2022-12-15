#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Bullet : public GameObject
    {
    private:
        VECTOR speed;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトのタグ</param>
        Bullet(ObjectTag tag);

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトのタグ</param>
        /// <param name="pos">初期位置</param>
        Bullet(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary<
        ~Bullet();

        /// <summary>
        /// 弾の更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// 弾の描画
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}// namespace My3dApp