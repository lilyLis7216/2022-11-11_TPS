#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** ゲームマネージャの生成*/
    My3dApp::GameManager::CreateInstance();

    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    /** ゲームループ*/
    My3dApp::GameManager::Loop();

    /** ゲームマネージャの削除*/
    My3dApp::GameManager::DeleteInstance();

    return 0;
}