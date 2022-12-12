#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Library/GamePad.h"
#include "Manager/AssetManager.h"
#include "Manager/GameManager.h"
#include "Manager/GameObjectManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // �Q�[���p�b�h�̐���
    My3dApp::GamePad::CreateInstance();

    // �A�Z�b�g�}�l�[�W���̐���
    My3dApp::AssetManager::CreateInstance();

    // �Q�[���}�l�[�W���̐���
    My3dApp::GameManager::CreateInstance();

    // �Q�[���I�u�W�F�N�g�}�l�[�W���̐���
    My3dApp::GameObjectManager::CreateInstance();

    // �ŏ��̃V�[�����Z�b�g
    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    // �Q�[�����[�v
    My3dApp::GameManager::Loop();

    // �Q�[���I�u�W�F�N�g�}�l�[�W���̍폜
    My3dApp::GameObjectManager::DeleteInstance();

    // �Q�[���}�l�[�W���̍폜
    My3dApp::GameManager::DeleteInstance();

    // �A�Z�b�g�}�l�[�W���̍폜
    My3dApp::AssetManager::DeleteInstance();

    // �Q�[���p�b�h�̍폜
    My3dApp::GamePad::DeleteInstance();

    return 0;
}