#include "HitEffect.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">初期位置</param>
    HitEffect::HitEffect(VECTOR pos, int efNum)
        : BaseEffect(pos)
    {
        // エフェクトの読み込み
        if (efNum == 0)
        {
            effectHandle = LoadEffekseerEffect("../asset/effect/softHit.efkefc", 25.0f);
        }
        else if (efNum == 1)
        {
            effectHandle = LoadEffekseerEffect("../asset/effect/burstHit.efkefc", 75.0f);
        }
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    HitEffect::~HitEffect()
    {
        // エフェクトの後始末
        DeleteEffekseerEffect(effectHandle);
    }

    /// <summary>
    /// ヒットエフェクトの更新
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void HitEffect::Update(float deltaTime)
    {
        // 再生していなければ
        if (!isPlay)
        {
            // 再生中にする
            isPlay = true;

            // 再生するエフェクトを入れる
            playEffect = PlayEffekseer3DEffect(effectHandle);
        }

        // エフェクトの位置設定
        SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);

        
        if (IsEffekseer3DEffectPlaying(playEffect) == -1)
        {
            isAlive = false;
        }
    }
}// namespace My3dApp