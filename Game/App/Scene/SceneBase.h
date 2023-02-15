#pragma once

namespace My3dApp
{
    /// <summary>
    /// �V�[���x�[�X�i���N���X�j
    /// </summary>
    class SceneBase
    {
    protected:
        // �V�[���\���p
        const char* text;

        int bgImage;

        int nextScene;

        int alpha;

        const int fadeSpeed = 2;

        enum NextScene
        {
            TITLE = 0,
            CONTROLS,
            PLAY,
            RESULT,
            QUIT,
        };

        int fadeState;

        enum FadeState
        {
            FADE_NONE = 0,
            FADE_OUT,
            FADE_IN,
        };

        void FadeIn();

        void FadeOut();

        void SetAlpha(int set) { alpha = set; }

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        SceneBase();

        /// <summary>
        /// ���z�f�X�g���N�^
        /// </summary>
        virtual ~SceneBase();

        /// <summary>
        /// �V�[���x�[�X�̍X�V�i�������z�֐��j
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        virtual SceneBase* Update(float deltaTime) = 0;

        /// <summary>
        /// �V�[���̕`��i�������z�֐��j
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// �V�[���؂�ւ��̓���
        /// </summary>
        /// <param name="sceneNum">�J�ڂ������V�[��</param>
        /// <returns></returns>
        SceneBase* CheckRetScene(int sceneNum);

        // �ȉ��f�o�b�O�p�֐�

        /// <summary>
        /// ���݂̃V�[���̊m�F�p
        /// </summary>
        void CheckNowScene();

    };
}// namespace My3dApp