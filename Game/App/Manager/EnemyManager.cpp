#include "EnemyManager.h"
#include "GameObjectManager.h"
#include "../GameObject/Enemy/NormalEnemy.h"
#include "../GameObject/Enemy/LightEnemy.h"
#include "../GameObject/Enemy/HeavyEnemy.h"

namespace My3dApp
{
    EnemyManager* EnemyManager::instance = nullptr;

    int EnemyManager::enemyNum;

    float EnemyManager::createInterval;

    int EnemyManager::count;

    EnemyManager::EnemyManager()
    {
        instance = nullptr;

        enemyNum = 0;

        createInterval = 0.0f;

        count = 0;
    }

    EnemyManager::~EnemyManager()
    {
    }

    void EnemyManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new EnemyManager();
        }
    }

    void EnemyManager::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    bool EnemyManager::IsCreateEnemy(float deltaTime, int enemyMaxNum)
    {
        createInterval -= deltaTime;

        if (enemyNum < enemyMaxNum && createInterval < 0)
        {
            createInterval = 5.0f;
            return true;
        }
        return false;
    }

    void EnemyManager::Update(float deltaTime, float timer, int enemyMaxNum)
    {
        if (EnemyManager::IsCreateEnemy(deltaTime, enemyMaxNum))
        {
            count++;

            if (count == 1)
            {
                GameObjectManager::Entry(new NormalEnemy(VGet((float)(rand() % 10 * 100), 1000.0f, (float)(rand() % 10 * 100))));
            }
            else if (count == 2)
            {
                if (timer < 40)
                {
                    GameObjectManager::Entry(new LightEnemy(VGet((float)(rand() % 10 * 100), 1000.0f, (float)(rand() % 10 * 100))));
                }
                else
                {
                    GameObjectManager::Entry(new NormalEnemy(VGet((float)(rand() % 10 * 100), 1000.0f, (float)(rand() % 10 * 100))));
                }
            }
            else if (count == 3)
            {
                if (timer < 20)
                {
                    GameObjectManager::Entry(new HeavyEnemy(VGet((float)(rand() % 10 * 100), 1000.0f, (float)(rand() % 10 * 100))));
                }
                else
                {
                    GameObjectManager::Entry(new NormalEnemy(VGet((float)(rand() % 10 * 100), 1000.0f, (float)(rand() % 10 * 100))));
                }
                count = 0;
            }
        }
    }

}// namespace My3dApp