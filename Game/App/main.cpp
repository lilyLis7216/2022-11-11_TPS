#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** �Q�[���}�l�[�W��*/
    My3dApp::GameManager* gameManager;

    /** �Q�[���}�l�[�W���̐���*/
    gameManager = new My3dApp::GameManager();

    /** �Q�[�����[�v*/
    gameManager->Loop();

    /** �Q�[���}�l�[�W���̍폜*/
    delete gameManager;

    return 0;
}