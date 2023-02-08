#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Manager/AssetManager.h"
#include "Manager/GameObjectManager.h"
#include "Library/GamePad.h"
#include "Library/UserInterface.h"
#include "Scene/Title.h"
#include "Scene/Play.h"

using namespace My3dApp;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // �Q�[���}�l�[�W���̐���
    GameManager::CreateInstance();

    if (GameManager::Init() != -1)
    {
        // �A�Z�b�g�}�l�[�W���̐���
        AssetManager::CreateInstance();

        // �Q�[���I�u�W�F�N�g�}�l�[�W���̐���
        GameObjectManager::CreateInstance();

        // �Q�[���p�b�h�̐���
        GamePad::CreateInstance();

        // UI�}�l�[�W���̐���
        UserInterface::CreateInstance();

        // �ŏ��̃V�[�����Z�b�g
        GameManager::SetFirstScene(new Title());

        // �Q�[�����[�v
        GameManager::Loop();

        // �Q�[���p�b�h�̍폜
        GamePad::DeleteInstance();

        // UI�}�l�[�W���̍폜
        UserInterface::DeleteInstance();

        // �Q�[���I�u�W�F�N�g�}�l�[�W���̍폜
        GameObjectManager::DeleteInstance();

        // �A�Z�b�g�}�l�[�W���̍폜
        AssetManager::DeleteInstance();
    }

    // �Q�[���}�l�[�W���̍폜
    GameManager::DeleteInstance();

    return 0;
}