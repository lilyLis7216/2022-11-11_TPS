#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * ���U���g�N���X
    * SceneBase���p�����Ă���
    */
    class Result : public SceneBase
    {
    public:
        /** �R���X�g���N�^*/
        Result();

        /** �f�X�g���N�^*/
        ~Result();

        /** ���U���g�V�[���̍X�V*/
        SceneType Update() override;

        /** ���U���g�V�[���̕`��*/
        void Draw() override;
    };

}/** namespace My3dApp*/
