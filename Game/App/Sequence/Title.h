#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * �^�C�g���N���X
    * �V�[���x�[�X���p�����Ă���
    */
    class Title : public SceneBase
    {
    public:
        Title();
        ~Title();

        SceneType Update() override;
        void Draw() override;
    };

}/** namespace My3dApp*/