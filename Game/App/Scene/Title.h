#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /**
    * �^�C�g���N���X
    * SceneBase���p�����Ă���
    */
    class Title : public SceneBase
    {
    public:
        /** �R���X�g���N�^*/
        Title();

        /** �f�X�g���N�^*/
        ~Title();

        /** �^�C�g���̍X�V*/
        SceneBase* Update(float deltaTime) override;

        /** �^�C�g���̕`��*/
        void Draw() override;
    };
}/** namespace My3dApp*/