#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"
#include "../Sequence/SceneBase.h"
#include "../Sequence/Title.h"
#include "../Sequence/StageSelect.h"

namespace My3dApp
{
    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
        Init();
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

    /**
    * �V�����V�[���𐶐�����֐�
    * ��قǏC���\��
    */
    SceneBase* CreateScene(SceneType now)
    {
        /** �Ԃ��V�[��*/
        SceneBase* retScene = nullptr;
        switch (now)
        {
        case SceneType::Scene_Title:
            retScene = new Title();
            break;
        case SceneType::Scene_StageSelect:
            retScene = new StageSelect();
            break;
        case SceneType::Scene_Play:
            break;
        case SceneType::Scene_Result:
            break;
        case SceneType::Scene_Exit:
            break;
        default:
            break;
        }

        return retScene;
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
        float waitFrameTime = 15900;

        /** �V�[���̐���*/
        SceneBase* scene = new Title();

        /** ���݂̃V�[���^�C�v*/
        SceneType nowSceneType = SceneType::Scene_Title;

        /** �O�̃V�[���^�C�v*/
        SceneType prevSceneType = nowSceneType;

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

            /** �V�[���̍X�V�ƌ��݂̃V�[���^�C�v�̕ۑ�*/
            nowSceneType = scene->Update();

            /** ��ʂ̏�����*/
            ClearDrawScreen();

            /** �V�[���̕`��*/
            scene->Draw();

            /** fps�m�F�p�i��ŏ����j*/
            DrawFormatString(100, 100, GetColor(255, 255, 255), "fps:%f", deltaTime);

            /** ����ʂ̓��e��\��ʂɔ��f������*/
            ScreenFlip();

            /** ���݂̃V�[���ƑO�̃V�[�����قȂ�����*/
            if (nowSceneType != prevSceneType)
            {
                /** �V�[���������*/
                if (scene)
                {
                    /** �V�[�������*/
                    delete scene;

                    /** �V�[����nullptr�ɐݒ肷��*/
                    scene = nullptr;
                }

                /** ���݂̃V�[����V��������ăV�[���ɓ����*/
                scene = CreateScene(nowSceneType);
            }

            /** 60fps����p���[�v*/
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            /** ���݂̃V�[���^�C�v��ۑ�����*/
            prevSceneType = nowSceneType;

            /** ���݂̃J�E���g��ۑ�����*/
            prevCount = nowCount;
        }

        /** �V�[���̉��*/
        delete scene;

        /** DxLib�̎g�p�I������*/
        DxLib_End();
    }

}/** namespace My3dApp*/
