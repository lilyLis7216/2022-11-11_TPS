#include "Play.h"
#include "DxLib.h"
#include "../Manager/GameObjectManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Map.h"
#include "../GameObject/Enemy.h"
#include "../Library/DebugGrid.h"

namespace My3dApp
{
    Play::Play()
    {
        text = "3.Play";
        GameObjectManager::Entry(new Player());
        GameObjectManager::Entry(new Camera(500, -500));
        GameObjectManager::Entry(new Map(VGet(0, -255, 0)));
        GameObjectManager::Entry(new Enemy(VGet(0, 0, 0)));
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        GameObjectManager::Update(deltaTime);

        GameObjectManager::Collision();

        retScene = CheckRetScene(3);

        return retScene;
    }

    void Play::Draw()
    {
        DrawGrid(3000, 30);

        GameObjectManager::Draw();

        CheckNowScene();
    }
}// namespace My3dApp