#include "GameManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Scene/SceneBase.h"
#include "../Scene/Title.h"
#include "../Scene/Explanation.h"
#include "../Scene/Play.h"
#include "../Scene/Result.h"
#include "../Library/GamePad.h"
#include "../Library/Shadow.h"

namespace My3dApp
{
    // �Q�[���}�l�[�W���C���X�^���X�ւ̃|�C���^��`
    GameManager* GameManager::instance = nullptr;

    SceneBase* GameManager::nowScene = nullptr;

    int GameManager::screenWidth;

    int GameManager::screenHeight;

    bool GameManager::fullScreen;

    int GameManager::score;

    int GameManager::combo;

    GameManager::GameManager()
    {
        // ��ʂ̉���������
        screenWidth = 0;

        // ��ʂ̍���������
        screenHeight = 0;

        // ��t���X�N���[��
        fullScreen = false;
    }

    GameManager::~GameManager()
    {
        // �e�Ǘ��p�̃C���X�^���X�폜
        Shadow::DeleteInstance();
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

    int GameManager::Init()
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

        // DirectX11���g�p����悤�ɂ���
        SetUseDirect3DVersion(DX_DIRECT3D_11);

        // DxLib�̏�����
        if (DxLib_Init() == -1)
        {
            return -1;
        }

        // Effekseer�̏�����
        if (Effekseer_Init(8000) == -1)
        {
            DxLib_End();
            return -1;
        }

        // �e�Ǘ��p�̃C���X�^���X����
        Shadow::CreateInstance();

        // �}�E�X�J�[�\����\�����Ȃ�
        SetMouseDispFlag(false);

        // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
        SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

        // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
        // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����
        Effekseer_SetGraphicsDeviceLostCallbackFunctions();

        // �`���𗠂ɐݒ肷��
        SetDrawScreen(DX_SCREEN_BACK);

        // Z�o�b�t�@��L���ɂ���
        SetUseZBuffer3D(true);

        // Z�o�b�t�@�ւ̏������݂�L���ɂ���
        SetWriteZBuffer3D(true);

        // �`�悷�鉜�s�������͈̔͂�ݒ�
        SetCameraNearFar(10.0f, 30000.0f);

        // �J�����̈ʒu�ƌ�����ݒ�
        SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 80.0f, -200.0f), VGet(0.0f, 80.0f, 0.0f));

        // ���C�g�̕�����ݒ�
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        // �V���h�E�}�b�v���z�肷�郉�C�g�̕����Z�b�g
        SetShadowMapLightDirection(Shadow::GetShadowMap(), VGet(-1.5f, -10.5f, 0.5f));

        // �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
        SetShadowMapDrawArea(Shadow::GetShadowMap(), VGet(-2000.0f, -1.0f, -2000.0f), VGet(2000.0f, 100.0f, 2000.0f));

        return 0;
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
        float waitFrameTime = 16667;

        SetBackgroundColor(135 , 206, 235);

        ResetScore();

        ResetCombo();

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
            //SetFontSize(25);
            //DrawFormatString(200, 10, GetColor(255, 255, 255), "fps:%f", deltaTime);
            //DrawFormatString(200, 10, GetColor(255, 255, 255), "lightNum:%d", GetEnableLightHandleNum());

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

            if (!tmpScene)
            {
                break;
            }

            // 60fps����p���[�v
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            // ���݂̃J�E���g��ۑ�����
            prevCount = nowCount;
        }

        // Effkseer�̏I������
        Effkseer_End();

        // DxLib�̏I������
        DxLib_End();
    }
}// namespace My3dApp