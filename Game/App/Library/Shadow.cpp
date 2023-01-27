#include "Shadow.h"
#include "DxLib.h"

namespace My3dApp
{
    Shadow* Shadow::instance = nullptr;

    int Shadow::shadowMap;

    Shadow::Shadow()
    {
        shadowMap = MakeShadowMap(2048, 2048);
        instance = this;
    }

    Shadow::~Shadow()
    {
        DeleteShadowMap(shadowMap);
    }

    void Shadow::CreateInstance()
    {
        if (!instance)
        {
            instance = new Shadow();
        }
    }

    void Shadow::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }
}