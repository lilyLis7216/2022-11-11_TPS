#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * �v���C�N���X
    * SceneBase���p�����Ă���
    */
    class Play : public SceneBase
    {
    public:
        /** �R���X�g���N�^*/
        Play();

        /** �f�X�g���N�^*/
        ~Play();

        /** �v���C�V�[���̍X�V*/
        SceneType Update() override;

        /** �v���C�V�[���̕`��*/
        void Draw() override;
    };
}