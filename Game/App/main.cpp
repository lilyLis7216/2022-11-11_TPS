#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/AssetManager.h"
#include "Manager/GameManager.h"
#include "Manager/GameObjectManager.h"
#include "Library/GamePad.h"
#include "Scene/Title.h"
#include "Scene/Play.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // アセットマネージャの生成
    My3dApp::AssetManager::CreateInstance();

    // ゲームマネージャの生成
    My3dApp::GameManager::CreateInstance();

    // ゲームオブジェクトマネージャの生成
    My3dApp::GameObjectManager::CreateInstance();

    // ゲームパッドの生成
    My3dApp::GamePad::CreateInstance();

    // 最初のシーンをセット
    My3dApp::GameManager::SetFirstScene(new My3dApp::Play());

    // ゲームループ
    My3dApp::GameManager::Loop();

    // ゲームパッドの削除
    My3dApp::GamePad::DeleteInstance();

    // ゲームオブジェクトマネージャの削除
    My3dApp::GameObjectManager::DeleteInstance();

    // ゲームマネージャの削除
    My3dApp::GameManager::DeleteInstance();

    // アセットマネージャの削除
    My3dApp::AssetManager::DeleteInstance();

    return 0;
}