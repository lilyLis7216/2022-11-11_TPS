#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

using namespace My3dApp;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** �Q�[���}�l�[�W���̏�����*/
    GameInstance.Init();

    /** �Q�[��*/
    GameInstance.Loop();

    return 0;
}