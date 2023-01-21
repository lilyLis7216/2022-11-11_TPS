#pragma once

namespace My3dApp
{
    /// <summary>
    /// �Q�[���}�l�[�W��
    /// </summary>
    class GameManager final
    {
    private:
        /// <summary>
        /// �R���X�g���N�^�i�V���O���g���j
        /// </summary>
        GameManager();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~GameManager();

        /// <summary>
        /// ���[�v�𔲂���ۂɎg�����͏����֐�
        /// </summary>
        /// <returns>���[�v�p���Ȃ�true �����łȂ����false</returns>
        static bool ProcessInput();

        // �Q�[���}�l�[�W���̗B��̃C���X�^���X
        static GameManager* instance;

        // ���݂̃V�[��
        static class SceneBase* nowScene;

        // ��ʉ���
        static int screenWidth;

        // ��ʏc��
        static int screenHeight;

        // �S��ʃt���O
        static bool fullScreen;

    public:
        /// <summary>
        /// �C���X�^���X�̐���
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// �C���X�^���X�̍폜
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// ����������
        /// </summary>
        static int Init();

        /// <summary>
        /// �ŏ��̃V�[���̐ݒ�
        /// </summary>
        /// <param name="scene">�ŏ��ɕ\���������V�[��</param>
        static void SetFirstScene(SceneBase* scene) { nowScene = scene; }

        /// <summary>
        /// �Q�[�����[�v
        /// </summary>
        static void Loop();

    };
}// namespace My3dApp