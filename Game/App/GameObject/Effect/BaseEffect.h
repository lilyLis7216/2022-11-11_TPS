#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �G�t�F�N�g�̊��N���X�iGameObject�p���j
    /// </summary>
    class BaseEffect : public GameObject
    {
    protected:
        // �G�t�F�N�g�n���h��
        int effectHandle;

        // �Đ�����G�t�F�N�g
        int playEffect;

        // �Đ�����
        bool isPlay;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        BaseEffect(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~BaseEffect();

        /// <summary>
        /// �G�t�F�N�g�̕`��
        /// </summary>
        void Draw() override;
    };
}// namespace My3dApp