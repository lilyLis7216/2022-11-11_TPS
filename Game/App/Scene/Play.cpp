#include "Play.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Manager/GameManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/EnemyManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Map.h"
#include "../GameObject/Enemy/NormalEnemy.h"
#include "../Library/DebugGrid.h"
#include "../Library/UserInterface.h"
#include "Result.h"

namespace My3dApp
{
    Play::Play()
        : timer(60.0f)
    {
        text = "3.Play";

        bgImage = -1;

        EnemyManager::CreateInstance();

        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        GameObjectManager::Entry(new NormalEnemy(VGet(0, 200, 1000)));
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();

        EnemyManager::DeleteInstance();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        timer -= deltaTime;

        SceneBase* retScene = this;

        EnemyManager::Update(deltaTime);

        GameObjectManager::Update(deltaTime);

        // エフェクシアの更新
        UpdateEffekseer3D();

        GameObjectManager::Collision();

        retScene = CheckRetScene(3);

        /*if (timer < 0)
        {
            retScene = new Result();
        }*/

        return retScene;
    }

    void Play::Draw()
    {
        //DrawGrid(3000, 30);

        GameObjectManager::Draw();

        DrawEffekseer3D();

        UserInterface::UIBox(170, 470, 20, 120, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));

        CheckNowScene();
    }
}// namespace My3dApp