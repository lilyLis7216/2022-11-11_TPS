#include "BaseEffect.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">初期位置</param>
    BaseEffect::BaseEffect(VECTOR pos)
        : GameObject(ObjectTag::Effect, pos)
        , effectHandle(-1)
        , playEffect(-1)
        , isPlay(false)
    {
        // 処理なし
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    BaseEffect::~BaseEffect()
    {
        // 処理なし
    }
}// namespace My3dApp