#pragma once

namespace My3dApp
{
    /**
    * �Q�[���}�l�[�W���N���X
    */
    class GameManager final
    {
    private:
        /**
        * �R���X�g���N�^
        *
        * �V���O���g��
        */
        GameManager();

        /** ���[�v�𔲂���ۂɎg�����͏����֐�*/
        bool ProcessInput();

        /** ��ʉ���*/
        int screenWidth;

        /** ��ʏc��*/
        int screenHeight;

        /** �S��ʃt���O*/
        bool fullScreen;

    public:
        /**
        * �Q�[���}�l�[�W���̃C���X�^���X�擾
        *
        * @return �Q�[���}�l�[�W���̃C���X�^���X
        */
        static GameManager& Instance()
        {
            static GameManager gameSystem;
            return gameSystem;
        }

        /** �f�X�g���N�^*/
        ~GameManager() {};

        /** �����������֐�*/
        void Init();

        /** �Q�[�����[�v�֐�*/
        void Loop();
    };

    /** �Q�[���}�l�[�W���C���X�^���X�̃}�N���쐬*/
    #define GameInstance GameManager::Instance()
}/** namespace My3dAppp*/