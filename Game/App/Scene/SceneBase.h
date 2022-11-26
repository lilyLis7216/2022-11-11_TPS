#pragma once

namespace My3dApp
{
    /**
    * �V�[���̊��N���X
    * �������z�֐��������Ă��钊�ۃN���X
    */
    class SceneBase
    {
    protected:
        /** �V�[���̕\�L�p�e�L�X�g*/
        const char* text;

    public:
        /** �R���X�g���N�^*/
        SceneBase();

        /** ���z�f�X�g���N�^*/
        virtual ~SceneBase();

        /** �V�[���̍X�V�i�������z�֐��j*/
        virtual SceneBase* Update() = 0;

        /** �V�[���̕`��i�������z�֐��j*/
        virtual void Draw() = 0;

        /** �V�[���̐؂�ւ�����*/
        SceneBase* CheckRetScene(int sceneNum);

        /**
        * �ȉ��f�o�b�O�p�֐�
        */

        /** ���݂̃V�[���̊m�F�֐�*/
        void CheckNowScene();

    };

}/** namespace My3dApp*/