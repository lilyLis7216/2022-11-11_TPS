#include "EnemyManager.h"

namespace My3dApp
{
    EnemyManager* EnemyManager::instance = nullptr;

    int EnemyManager::enemyNum;

    float EnemyManager::createInterval;

    EnemyManager::EnemyManager()
    {
        instance = nullptr;

        enemyNum = 0;

        createInterval = 0.0f;
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

    bool EnemyManager::IsCreateEnemy(float deltaTime)
    {
        createInterval -= deltaTime;

        if (enemyNum < enemyNumMax && createInterval < 0)
        {
            createInterval = 3.0f;
            return true;
        }
        return false;
    }

}// namespace My3dApp