#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"
#include "../Scene/SceneBase.h"
#include "../Scene/Title.h"
#include "../Scene/StageSelect.h"
#include "../Scene/Play.h"
#include "../Scene/Result.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    // �Q�[���}�l�[�W���C���X�^���X�ւ̃|�C���^��`
    GameManager* GameManager::instance = nullptr;

    SceneBase* GameManager::nowScene = nullptr;

    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
        Init();
    }

    GameManager::~GameManager()
    {
        // �����Ȃ�
    }

    void GameManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new GameManager();
        }
    }

    void GameManager::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    bool GameManager::ProcessInput()
    {
        // �G���[���ł��A�������̓E�B���h�E������ꂽ��
        if (ProcessMessage() != 0)
        {
            // ���[�v�̃t���O��|��
            return false;
        }

        // ESC�L�[�������ꂽ��
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            // ���[�v�̃t���O��|��
            return false;
        }

        return true;
    }

    void GameManager::Init()
    {
        // ��ʂ̉�����1920�ɐݒ�
        screenWidth = 1920;

        // ��ʂ̏c����1080�ɐݒ�
        screenHeight = 1080;

        // �S��ʂɂ���
        fullScreen = true;

        // �S��ʂ̃t���O�������Ă��Ȃ����
        if (!fullScreen)
        {
            // �E�B���h�E���[�h�ɂ���
            ChangeWindowMode(TRUE);
        }

        // ��ʃ��[�h�̐ݒ�
        SetGraphMode(screenWidth, screenHeight, 32);

        // DxLib�̏���������
        DxLib_Init();

        // �}�E�X�J�[�\����\�����Ȃ�
        SetMouseDispFlag(false);

        // Z�o�b�t�@��L���ɂ���
        SetUseZBuffer3D(true);

        // Z�o�b�t�@�ւ̏������݂�L���ɂ���
        SetWriteZBuffer3D(true);

        // 
        SetCameraNearFar(10.0f, 30000.0f);

        // 
        SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0.0f, 80.0f, 0.0f));
    }

    void GameManager::Loop()
    {
        // ���[�v�t���O
        bool gameLoop = true;

        // ���t���[���̃J�E���g
        LONGLONG nowCount = GetNowHiPerformanceCount();

        // �O�t���[���̃J�E���g
        LONGLONG prevCount = nowCount;

        // �ҋ@�t���[�����ԁi60fps�z��j
        // 1/60 = 1.66666...
        // 16000�}�C�N���b = 16�~���b = 0.016�b
        float waitFrameTime = 15900;

        SetBackgroundColor(128, 128, 128);

        // ���[�v�{��
        while (gameLoop)
        {
            // ���t���[���ƑO�t���[���Ƃ̍���
            float deltaTime;

            // ���t���[���J�E���g�̍X�V
            nowCount = GetNowHiPerformanceCount();

            // ������100������1�ɂ��ĕۑ�����i�}�C�N���b���Z�j
            deltaTime = (nowCount - prevCount) / 1000000.0f;

            // �Q�[���p�b�h�̍X�V
            GamePad::Update();

            // ���[�v�p���̊m�F
            gameLoop = ProcessInput();

            // ���V�[��
            SceneBase* tmpScene;

            // �V�[���̍X�V�ƌ��݂̃V�[���̕ۑ�
            tmpScene = nowScene->Update(deltaTime);

            // ��ʂ̏�����
            ClearDrawScreen();

            // �V�[���̕`��
            nowScene->Draw();

            // fps�m�F�p�i��ŏ����j
            DrawFormatString(100, 100, GetColor(255, 255, 255), "fps:%f", deltaTime);

            // ����ʂ̓��e��\��ʂɔ��f������
            ScreenFlip();

            // �X�V�O�̃V�[���ƍX�V��̃V�[�����قȂ�����
            if (nowScene != tmpScene)
            {
                // �V�[�������
                delete nowScene;

                // �V�����V�[��������
                nowScene = tmpScene;
            }

            // 60fps����p���[�v
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            // ���݂̃J�E���g��ۑ�����
            prevCount = nowCount;
        }

        // DxLib�̎g�p�I������
        DxLib_End();
    }
}// namespace My3dApp
