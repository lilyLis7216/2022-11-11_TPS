#include "AssetManager.h"

namespace My3dApp
{
    AssetManager* AssetManager::instance = nullptr;

    AssetManager::AssetManager()
    {
    }

    AssetManager::~AssetManager()
    {
    }

    void AssetManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new AssetManager();
        }
    }

    void AssetManager::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

}/** namespace My3dApp*/