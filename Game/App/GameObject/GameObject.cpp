#include "GameObject.h"

namespace My3dApp
{
    GameObject::GameObject(ObjectTag tag)
        : GameObject(tag, initPos)
    {
    }

    GameObject::GameObject(ObjectTag tag, VECTOR pos)
        : tag(tag)
        , modelHandle(-1)
    {
        this->pos = pos;
    }

    GameObject::~GameObject()
    {
        /** モデルの後始末*/
        if (modelHandle == -1)
        {
            modelHandle = -1;
        }
    }

    void GameObject::Draw()
    {
        /** 処理なし*/
    }
}/** namespace My3dApp*/