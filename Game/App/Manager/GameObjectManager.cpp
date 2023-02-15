#include "GameObjectManager.h"
#include "../Library/Shadow.h"

namespace My3dApp
{
    // ゲームオブジェクトマネージャインスタンスへのポインタ定義
    GameObjectManager* GameObjectManager::instance = nullptr;

    GameObjectManager::GameObjectManager()
        : pendingObjects()
        , objects()
    {
        instance = nullptr;
    }

    GameObjectManager::~GameObjectManager()
    {
        ReleaseAllObject();
    }

    void GameObjectManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new GameObjectManager();
        }
    }

    void GameObjectManager::DeleteInstance()
    {
        ReleaseAllObject();

        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void GameObjectManager::Update(float deltaTime)
    {

        for (auto& tag : ObjectTagAll)
        {
            // 該当タグにあるすべてのオブジェクトの更新
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                instance->objects[tag][i]->Update(deltaTime);
            }
        }

        for (auto pending : instance->pendingObjects)
        {
            ObjectTag tag = pending->GetTag();
            instance->objects[tag].emplace_back(pending);
        }

        instance->pendingObjects.clear();

        vector<GameObject*> deadObjects;
        for (auto& tag : ObjectTagAll)
        {
            for (auto obj : instance->objects[tag])
            {
                if (!obj->GetAlive())
                {
                    deadObjects.emplace_back(obj);
                }
            }

            instance->objects[tag].erase(remove_if(begin(instance->objects[tag]), end(instance->objects[tag]), 
                [](GameObject* g) {return !g->GetAlive(); }), cend(instance->objects[tag]));
        }

        // 死んでいるGameObjectをここでdelete
        while (!deadObjects.empty())
        {
            delete deadObjects.back();
            deadObjects.pop_back();
        }
    }

    void GameObjectManager::Draw()
    {
        // シャドウマップへの描画の準備
        ShadowMap_DrawSetup(Shadow::GetShadowMap());

        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                if (instance->objects[tag][i]->GetVisible())
                {
                    instance->objects[tag][i]->Draw();
                }
            }
        }

        // シャドウマップへの描画を終了
        ShadowMap_DrawEnd();

        for (auto& tag : ObjectTagAll)
        {
            if (tag != ObjectTag::Map)
            {
                // 描画に使用するシャドウマップを設定
                SetUseShadowMap(0, Shadow::GetShadowMap());
            }
            else
            {
                SetUseShadowMap(1, Shadow::GetShadowMap());
            }
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                if (instance->objects[tag][i]->GetVisible())
                {
                    instance->objects[tag][i]->Draw();
                }
            }
        }

        // 描画に使用するシャドウマップの設定を解除
        SetUseShadowMap(0, -1);
        SetUseShadowMap(1, -1);

        auto tag = ObjectTag::Enemy;
        for (int i = 0; i < instance->objects[tag].size(); ++i)
        {
            if (instance->objects[tag][i]->GetVisible())
            {
                instance->objects[tag][i]->DamageParView(1);
            }
        }
    }

    void GameObjectManager::Entry(GameObject* newObject)
    {
        // 保留オブジェクトに一時保存
        instance->pendingObjects.push_back(newObject);
    }

    void GameObjectManager::Release(GameObject* releaseObject)
    {
        auto pending = instance->pendingObjects;
        auto itr = find(pending.begin(), pending.end(), releaseObject);
        if (itr != pending.end())
        {
            iter_swap(itr, pending.end() - 1);
            pending.pop_back();

            return;
        }

        auto object = instance->objects[releaseObject->GetTag()];
        itr = find(object.begin(), object.end(), releaseObject);
        if (itr != object.end())
        {
            iter_swap(itr, object.end() - 1);
            delete object.back();
        }
    }

    void GameObjectManager::ReleaseAllObject()
    {
        while (!instance->pendingObjects.empty())
        {
            delete instance->pendingObjects.back();
            instance->pendingObjects.pop_back();
        }

        for (auto& tag : ObjectTagAll)
        {
            while (!instance->objects[tag].empty())
            {
                delete instance->objects[tag].back();
                instance->objects[tag].pop_back();
            }
        }
    }

    void GameObjectManager::Collision()
    {
        // メインのタグ
        ObjectTag mainTag;

        // ペアのタグ
        ObjectTag pairTag;

        // プレイヤーの当たり判定
        mainTag = ObjectTag::Player;
        for (int playerNum = 0; playerNum < instance->objects[mainTag].size(); ++playerNum)
        {
            // マップとの当たり判定
            pairTag = ObjectTag::Map;
            for (int mapNum = 0; mapNum < instance->objects[pairTag].size(); ++mapNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][mapNum]);
            }

            // エネミーとの当たり判定
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }

            // エネミー弾との当たり判定
            pairTag = ObjectTag::EnemyBullet;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // エネミー弾との当たり判定
            pairTag = ObjectTag::EnemyBulletS;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // エネミー弾との当たり判定
            pairTag = ObjectTag::EnemyBulletM;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // エネミー弾との当たり判定
            pairTag = ObjectTag::EnemyBulletL;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }
        }

        // プレイヤー弾の当たり判定
        mainTag = ObjectTag::PlayerBullet;
        for (int pBulletNum = 0; pBulletNum < instance->objects[mainTag].size(); ++pBulletNum)
        {
            // 敵との当たり判定
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][pBulletNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }
        }

        // プレイヤー弾の当たり判定
        mainTag = ObjectTag::PlayerBulletCharge;
        for (int pBulletNum = 0; pBulletNum < instance->objects[mainTag].size(); ++pBulletNum)
        {
            // 敵との当たり判定
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][pBulletNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }
        }

        // エネミーの当たり判定
        mainTag = ObjectTag::Enemy;
        for (int enemyNum = 0; enemyNum < instance->objects[mainTag].size(); ++enemyNum)
        {
            // マップとの当たり判定
            pairTag = ObjectTag::Map;
            for (int mapNum = 0; mapNum < instance->objects[pairTag].size(); ++mapNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][mapNum]);
            }

            // 自身を除くエネミーとの当たり判定
            pairTag = ObjectTag::Enemy;
            for (int anotherEnemyNum = 0; anotherEnemyNum < instance->objects[pairTag].size(); ++anotherEnemyNum)
            {
                if (enemyNum != anotherEnemyNum)
                {
                    instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][anotherEnemyNum]);
                }
            }

            pairTag = ObjectTag::PlayerBullet;
            for (int pBulletNum = 0; pBulletNum < instance->objects[pairTag].size(); ++pBulletNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][pBulletNum]);
            }

            pairTag = ObjectTag::PlayerBulletCharge;
            for (int pBulletNum = 0; pBulletNum < instance->objects[pairTag].size(); ++pBulletNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][pBulletNum]);
            }
        }

        // エネミー弾の当たり判定
        mainTag = ObjectTag::EnemyBullet;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // プレイヤーとの当たり判定
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // エネミー弾の当たり判定
        mainTag = ObjectTag::EnemyBulletS;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // プレイヤーとの当たり判定
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // エネミー弾の当たり判定
        mainTag = ObjectTag::EnemyBulletM;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // プレイヤーとの当たり判定
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // エネミー弾の当たり判定
        mainTag = ObjectTag::EnemyBulletL;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // プレイヤーとの当たり判定
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }
    }

    GameObject* GameObjectManager::GetFirstGameObject(ObjectTag tag)
    {
        if (instance->objects[tag].size() == 0)
        {
            return nullptr;
        }
        return instance->objects[tag][0];
    }
}// namespace My3dApp