#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"

namespace My3dApp
{
    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
    }

    bool GameManager::ProcessInput()
    {
        /** �G���[���ł��A�������̓E�B���h�E������ꂽ��*/
        if (ProcessMessage() != 0)
        {
            /** ���[�v�̃t���O��|��*/
            return false;
        }

        /** �G�X�P�[�v�L�[�������ꂽ��*/
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            /** ���[�v�̃t���O��|��*/
            return false;
        }

        return true;
    }

    void GameManager::Init()
    {
        /** ��ʂ̉�����1920�ɐݒ�*/
        screenWidth = 1920;

        /** ��ʂ̏c����1080�ɐݒ�*/
        screenHeight = 1080;

        /** �S��ʂɂ���*/
        fullScreen = true;

        /** �S��ʂ̃t���O�������Ă��Ȃ��Ƃ�*/
        if (!fullScreen)
        {
            ChangeWindowMode(TRUE);
        }

        /** ��ʃ��[�h�̐ݒ�*/
        SetGraphMode(screenWidth, screenHeight, 32);

        /** DxLib�̏���������*/
        DxLib_Init();

        /** �}�E�X�J�[�\����\�����Ȃ�*/
        SetMouseDispFlag(false);
    }

    void GameManager::Loop()
    {
        /** ���[�v�t���O*/
        bool gameLoop = true;

        /** ���t���[���̃J�E���g*/
        LONGLONG nowCount = GetNowHiPerformanceCount();

        /** �O�t���[���̃J�E���g*/
        LONGLONG prevCount = nowCount;

        /**
        * �ҋ@�t���[�����ԁi60fps�z��j
        * 1/60 = 1.66666...
        * 16000�}�C�N���b = 16�~���b = 0.016�b
        */
        float waitFrameTime = 15500;

        /** ���[�v�{��*/
        while (gameLoop)
        {
            /** ���t���[���ƑO�t���[���Ƃ̍���*/
            float deltaTime;

            /** ���t���[���J�E���g�̍X�V*/
            nowCount = GetNowHiPerformanceCount();

            /** ������100������1�ɂ��ĕۑ�����i�}�C�N���b���Z�j*/
            deltaTime = (nowCount - prevCount) / 1000000.0f;

            /** ���[�v�p���̊m�F*/
            gameLoop = ProcessInput();

            /** ��ʂ̏�����*/
            ClearDrawScreen();

            /** ����ʂ̓��e��\��ʂɔ��f������*/
            ScreenFlip();

            /** 60fps����p���[�v*/
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            /** ���[�v���I��钼�O�ɑO�t���[���J�E���g�̍X�V������*/
            prevCount = nowCount;
        }

        /** DxLib�̎g�p�I������*/
        DxLib_End();
    }
}
