#include "BaseEffect.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�����ʒu</param>
    BaseEffect::BaseEffect(VECTOR pos)
        : GameObject(ObjectTag::Effect, pos)
        , effectHandle(0)
        , playEffect(-1)
        , isPlay(false)
    {
        // �����Ȃ�
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    BaseEffect::~BaseEffect()
    {
        // �����Ȃ�
    }

    /// <summary>
    /// �G�t�F�N�g�̕`��
    /// </summary>
    void BaseEffect::Draw()
    {
        DrawEffekseer3D();
    }
}// namespace My3dApp