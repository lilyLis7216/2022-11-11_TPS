#pragma once
#include "SceneBase.h"

namespace Sequence
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

}/** namespace Sequence*/