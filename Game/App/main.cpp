#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Library/GamePad.h"
#include "Manager/AssetManager.h"
#include "Manager/GameManager.h"
#include "Manager/GameObjectManager.h"
#include "Scene/Title.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ゲームパッドの生成
    My3dApp::GamePad::CreateInstance();

    // アセットマネージャの生成
    My3dApp::AssetManager::CreateInstance();

    // ゲームマネージャの生成
    My3dApp::GameManager::CreateInstance();

    // ゲームオブジェクトマネージャの生成
    My3dApp::GameObjectManager::CreateInstance();

    // 最初のシーンをセット
    My3dApp::GameManager::SetFirstScene(new My3dApp::Title());

    // ゲームループ
    My3dApp::GameManager::Loop();

    // ゲームオブジェクトマネージャの削除
    My3dApp::GameObjectManager::DeleteInstance();

    // ゲームマネージャの削除
    My3dApp::GameManager::DeleteInstance();

    // アセットマネージャの削除
    My3dApp::AssetManager::DeleteInstance();

    // ゲームパッドの削除
    My3dApp::GamePad::DeleteInstance();

    return 0;
}