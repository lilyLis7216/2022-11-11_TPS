#pragma once
#include "SceneBase.h"

namespace My3dApp
{
    /**
    * �X�e�[�W�Z���N�g�N���X
    * SceneBase���p�����Ă���
    */
    class StageSelect : public SceneBase
    {
    public:
        /** �R���X�g���N�^*/
        StageSelect();

        /** �f�X�g���N�^*/
        ~StageSelect();

        /** �X�e�[�W�Z���N�g�̍X�V*/
        SceneBase* Update(float deltaTime) override;

        /** �X�e�[�W�Z���N�g�̕`��*/
        void Draw() override;
    };

}/** namespace My3dApp*/