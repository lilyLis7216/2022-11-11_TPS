#include "Play.h"
#include "DxLib.h"
#include "../Manager/GameObjectManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Map.h"
#include "../Library/DebugGrid.h"

namespace My3dApp
{
    Play::Play()
    {
        text = "3.Play";
        GameObjectManager::Entry(new Player());
        GameObjectManager::Entry(new Map(VGet(0, -255, 0)));
    }

    Play::~Play()
    {
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
        CheckNowScene();

        DrawGrid(3000, 30);

        GameObjectManager::Draw();
    }
}/** namespace My3dApp*/