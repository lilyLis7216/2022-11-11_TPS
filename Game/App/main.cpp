#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Manager/AssetManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** アセットマネージャの生成*/
    My3dApp::AssetManager::CreateInstance();

    /** ゲームマネージャの生成*/
    My3dApp::GameManager::CreateInstance();

    /** 最初のシーンをセット*/
    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    /** ゲームループ*/
    My3dApp::GameManager::Loop();

    /** ゲームマネージャの削除*/
    My3dApp::GameManager::DeleteInstance();

    /** アセットマネージャの削除*/
    My3dApp::AssetManager::DeleteInstance();

    return 0;
}