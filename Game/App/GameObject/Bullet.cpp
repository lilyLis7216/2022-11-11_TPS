#include "Bullet.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    Bullet::Bullet(ObjectTag tag, VECTOR pos)
        : GameObject(tag, pos)
    {
        //modelHandle = AssetManager::GetMesh("../asset/model/bullet/bullet.mv1");

        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

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