#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// ���U���g�V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class Result : public SceneBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Result();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Result();

        /// <summary>
        /// ���U���g�V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// ���U���g�V�[���̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp