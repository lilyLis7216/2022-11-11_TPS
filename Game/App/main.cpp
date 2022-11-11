#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

using namespace My3dApp;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** ゲームマネージャの初期化*/
    GameInstance.Init();

    /** ゲーム*/
    GameInstance.Loop();

    return 0;
}