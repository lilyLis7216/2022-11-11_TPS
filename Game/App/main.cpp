#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** �Q�[���}�l�[�W���̃C���X�^���X����*/
    My3dApp::GameManager* gameMngr = new My3dApp::GameManager();

    /** �Q�[�����[�v*/
    gameMngr->Loop();

    /** �Q�[���}�l�[�W���̃C���X�^���X�폜*/
    delete gameMngr;

    return 0;
}