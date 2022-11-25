#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** �Q�[���}�l�[�W���̐���*/
    My3dApp::GameManager::CreateInstance();

    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    /** �Q�[�����[�v*/
    My3dApp::GameManager::Loop();

    /** �Q�[���}�l�[�W���̍폜*/
    My3dApp::GameManager::DeleteInstance();

    return 0;
}