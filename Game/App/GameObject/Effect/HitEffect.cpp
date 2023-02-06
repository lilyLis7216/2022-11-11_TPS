#include "HitEffect.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�����ʒu</param>
    HitEffect::HitEffect(VECTOR pos, int efNum)
        : BaseEffect(pos)
    {
        // �G�t�F�N�g�̓ǂݍ���
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
    /// �f�X�g���N�^
    /// </summary>
    HitEffect::~HitEffect()
    {
        // �G�t�F�N�g�̌�n��
        DeleteEffekseerEffect(effectHandle);
    }

    /// <summary>
    /// �q�b�g�G�t�F�N�g�̍X�V
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void HitEffect::Update(float deltaTime)
    {
        // �Đ����Ă��Ȃ����
        if (!isPlay)
        {
            // �Đ����ɂ���
            isPlay = true;

            // �Đ�����G�t�F�N�g������
            playEffect = PlayEffekseer3DEffect(effectHandle);
        }

        // �G�t�F�N�g�̈ʒu�ݒ�
        SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);

        
        if (IsEffekseer3DEffectPlaying(playEffect) == -1)
        {
            isAlive = false;
        }
    }
}// namespace My3dApp