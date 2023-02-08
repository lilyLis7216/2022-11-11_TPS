#pragma warning(disable:28251)
#include <windows.h>
#include "Dxlib.h"
#include "Manager/GameManager.h"
#include "Manager/AssetManager.h"
#include "Manager/GameObjectManager.h"
#include "Library/GamePad.h"
#include "Library/UserInterface.h"
#include "Scene/Title.h"
#include "Scene/Play.h"

using namespace My3dApp;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ゲームマネージャの生成
    GameManager::CreateInstance();

    if (GameManager::Init() != -1)
    {
        // アセットマネージャの生成
        AssetManager::CreateInstance();

        // ゲームオブジェクトマネージャの生成
        GameObjectManager::CreateInstance();

        // ゲームパッドの生成
        GamePad::CreateInstance();

        // UIマネージャの生成
        UserInterface::CreateInstance();

        // 最初のシーンをセット
        GameManager::SetFirstScene(new Title());

        // ゲームループ
        GameManager::Loop();

        // ゲームパッドの削除
        GamePad::DeleteInstance();

        // UIマネージャの削除
        UserInterface::DeleteInstance();

        // ゲームオブジェクトマネージャの削除
        GameObjectManager::DeleteInstance();

        // アセットマネージャの削除
        AssetManager::DeleteInstance();
    }

    // ゲームマネージャの削除
    GameManager::DeleteInstance();

    return 0;
}