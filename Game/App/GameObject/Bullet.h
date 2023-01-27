#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Bullet : public GameObject
    {
    private:
        VECTOR speed;

        VECTOR dir;

        float boost;

        float deadCount;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="setTag">オブジェクトのタグ</param>
        /// <param name="initPos">初期位置</param>
        /// <param name="initDir">向き</param>
        Bullet(ObjectTag setTag, VECTOR initPos, VECTOR initDir);

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