#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** ゲームマネージャのインスタンス生成*/
    My3dApp::GameManager* gameMngr = new My3dApp::GameManager();

    /** ゲームループ*/
    gameMngr->Loop();

    /** ゲームマネージャのインスタンス削除*/
    delete gameMngr;

    return 0;
}