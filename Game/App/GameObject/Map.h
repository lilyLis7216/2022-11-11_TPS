#pragma once

#include "GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// �}�b�v�i�h���N���X�A�p�����F�Q�[���I�u�W�F�N�g�j
    /// </summary>
    class Map : public GameObject
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="pos">�����ʒu</param>
        Map(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Map();

        /// <summary>
        /// �}�b�v�̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

        /// <summary>
        /// �}�b�v�̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp