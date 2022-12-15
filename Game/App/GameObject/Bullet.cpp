#include "Bullet.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    Bullet::Bullet(ObjectTag tag)
        : Bullet(tag, initPos)
    {
    }

    Bullet::Bullet(ObjectTag tag, VECTOR pos)
        : GameObject(tag, pos)
    {
        //modelHandle = AssetManager::GetMesh("../Asset/Model/Bullet/");

        speed = VGet(0, 0, 0);
    }

    Bullet::~Bullet()
    {
    }

    void Bullet::Update(float deltaTime)
    {
    }

    void Bullet::Draw()
    {
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Bullet::OnCollisionEnter(const GameObject* other)
    {
    }
}// namespace My3dApp