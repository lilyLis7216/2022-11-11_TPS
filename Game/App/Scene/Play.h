#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// �v���C�V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class Play : public SceneBase
    {
    private:

        // �^�C�}�[
        float timer;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Play();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Play();

        /// <summary>
        /// �v���C�V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// �v���C�V�[���̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp