#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// �X�e�[�W�Z���N�g�V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class StageSelect : public SceneBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        StageSelect();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~StageSelect();

        /** �X�e�[�W�Z���N�g�̍X�V*/

        /// <summary>
        /// �X�e�[�W�Z���N�g�V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// �X�e�[�W�Z���N�g�V�[���̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp