#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Manager/AssetManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** �A�Z�b�g�}�l�[�W���̐���*/
    My3dApp::AssetManager::CreateInstance();

    /** �Q�[���}�l�[�W���̐���*/
    My3dApp::GameManager::CreateInstance();

    /** �ŏ��̃V�[�����Z�b�g*/
    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    /** �Q�[�����[�v*/
    My3dApp::GameManager::Loop();

    /** �Q�[���}�l�[�W���̍폜*/
    My3dApp::GameManager::DeleteInstance();

    /** �A�Z�b�g�}�l�[�W���̍폜*/
    My3dApp::AssetManager::DeleteInstance();

    return 0;
}