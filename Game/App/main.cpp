#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Control/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** ゲームマネージャ*/
    My3dApp::GameManager* gameManager;

    /** ゲームマネージャの生成*/
    gameManager = new My3dApp::GameManager();

    /** ゲームループ*/
    gameManager->Loop();

    /** ゲームマネージャの削除*/
    delete gameManager;

    return 0;
}