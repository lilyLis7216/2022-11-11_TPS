#include "Shadow.h"
#include "DxLib.h"

namespace My3dApp
{
    Shadow* Shadow::instance = nullptr;

    int Shadow::shadowMap;

    Shadow::Shadow()
    {
        //shadowMap = MakeShadowMap(1024, 1024);
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