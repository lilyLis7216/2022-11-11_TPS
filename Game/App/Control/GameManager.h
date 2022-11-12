#pragma once

namespace My3dApp
{
    /**
    * �Q�[���}�l�[�W���N���X
    */
    class GameManager final
    {
    private:
        /** ���[�v�𔲂���ۂɎg�����͏����֐�*/
        bool ProcessInput();

        /** ��ʉ���*/
        int screenWidth;

        /** ��ʏc��*/
        int screenHeight;

        /** �S��ʃt���O*/
        bool fullScreen;

    public:
        /** �R���X�g���N�^*/
        GameManager();

        /** �f�X�g���N�^*/
        ~GameManager() {};

        /** �����������֐�*/
        void Init();

        /** �Q�[�����[�v�֐�*/
        void Loop();
    };

}/** namespace My3dAppp*/