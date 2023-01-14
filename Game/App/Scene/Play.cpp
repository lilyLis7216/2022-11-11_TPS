#include "Play.h"
#include "DxLib.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/GameManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Map.h"
#include "../GameObject/Enemy.h"
#include "../Library/DebugGrid.h"
#include "Result.h"

namespace My3dApp
{
    Play::Play()
        : timer(60.0f)
    {
        text = "3.Play";

        bgImage = -1;

        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(750, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        GameObjectManager::Entry(new Enemy(VGet(0, 0, 1000)));
        GameObjectManager::Entry(new Enemy(VGet(0, 0, -1000)));
        GameObjectManager::Entry(new Enemy(VGet(1000, 0, 0)));
        GameObjectManager::Entry(new Enemy(VGet(-1000, 0, 0)));
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        timer -= deltaTime;

        SceneBase* retScene = this;

        GameObjectManager::Update(deltaTime);

        GameObjectManager::Collision();

        retScene = CheckRetScene(3);

        if (timer < 0)
        {
            retScene = new Result();
        }

        return retScene;
    }

    void Play::Draw()
    {
        //DrawGrid(3000, 30);

        GameObjectManager::Draw();

        CheckNowScene();
    }
}// namespace My3dApp