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

        /** ���U���g�̍X�V*/
        SceneBase* Update() override;

        /** ���U���g�̕`��*/
        void Draw() override;
    };

}/** namespace My3dApp*/