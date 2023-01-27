#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="tag">オブジェクトの種類</param>
    BaseBullet::BaseBullet(ObjectTag tag)
        : GameObject(tag)
    {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    BaseBullet::~BaseBullet()
    {
        // 処理なし
    }
}// namespace My3dApp