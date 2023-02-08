#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// �^�C�g���V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class Title : public SceneBase
    {
    private:
        int titleModel;

        int startModel;

        int exitModel;

        float rotateCount;

        void MoveModel(float deltaTime);

        int selectState;

        enum SelectState
        {
            START = 0,
            EXIT,
        };

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Title();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Title();

        /// <summary>
        /// �^�C�g���V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// �^�C�g���V�[���̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp