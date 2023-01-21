#pragma once

#include <vector>

using namespace std;

namespace My3dApp
{
    class EnemyManager final
    {
    private:
        EnemyManager();

        ~EnemyManager();

        static EnemyManager* instance;

        static const int enemyNumMax = 4;

        static int enemyNum;

        static float createInterval;

    public:

        static void CreateInstance();

        static void DeleteInstance();

        static void AddNum() { enemyNum++; }

        static void SubNum() { enemyNum--; }

        static void ResetNum() { enemyNum = 0; }

        static bool IsCreateEnemy(float deltaTime);
    };
}// namespace My3dApp