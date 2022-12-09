#pragma once

namespace My3dApp
{
    /**
    * �Q�[���}�l�[�W���N���X
    */
    class GameManager final
    {
    private:
        /** �R���X�g���N�^*/
        GameManager();

        /** �f�X�g���N�^*/
        ~GameManager();

        /** �����������֐�*/
        void Init();

        /** ���[�v�𔲂���ۂɎg�����͏����֐�*/
        static bool ProcessInput();

        /** �}�l�[�W���̃C���X�^���X*/
        static GameManager* instance;

        /** �V�[��*/
        static class SceneBase* nowScene;

        /** ��ʉ���*/
        int screenWidth;

        /** ��ʏc��*/
        int screenHeight;

        /** �S��ʃt���O*/
        bool fullScreen;

    public:
        /** �C���X�^���X�̐���*/
        static void CreateInstance();

        /** �C���X�^���X�̍폜*/
        static void DeleteInstance();

        /** �n�߂�V�[���̎w��*/
        static void SetFirstScene(SceneBase* scene) { nowScene = scene; }

        /** �Q�[�����[�v�֐�*/
        static void Loop();
    };
}/** namespace My3dAppp*/