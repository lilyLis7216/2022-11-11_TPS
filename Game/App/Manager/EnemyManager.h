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

        static const int enemyNumMax = 1;

        static int enemyNum;

        static float createInterval;

        static int count;

    public:

        static void CreateInstance();

        static void DeleteInstance();

        static void AddNum() { enemyNum++; }

        static void SubNum() { enemyNum--; }

        static void ResetNum() { enemyNum = 0; }

        static bool IsCreateEnemy(float deltaTime);

        static void Update(float deltaTime);
    };
}// namespace My3dApp