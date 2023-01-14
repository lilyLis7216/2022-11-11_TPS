#include "Bullet.h"
#include "../Manager/AssetManager.h"
#include "../Library/Calc3D.h"

namespace My3dApp
{
    Bullet::Bullet(ObjectTag tag, VECTOR pos, VECTOR dir)
        : GameObject(tag)
        , deadCount(5.0f)
        , boost(0)
    {
        modelHandle = -1;

        if (this->tag == ObjectTag::PlayerBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/playerBullet.mv1");
        }
        else if (this->tag == ObjectTag::EnemyBullet)
        {
            modelHandle = AssetManager::GetMesh("../asset/model/bullet/enemyBullet.mv1");
        }

        this->pos = pos;

        this->pos.y = 80.0f;

        MV1SetPosition(modelHandle, this->pos);

        MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

        this->dir = dir;

        speed = VGet(0, 0, 0);

        if (tag == ObjectTag::PlayerBullet)
        {
            boost = 800.0f;
        }
        else if (tag == ObjectTag::EnemyBullet)
        {
            boost = 1000.0f;
        }

        // �����蔻���ނ̏�����
        collisionType = CollisionType::Sphere;

        // ���̃��[�J�����S���W�̏�����
        collisionSphere.localCenter = VGet(0, 0, 0);

        // ���̔��a�̏�����
        collisionSphere.radius = 10.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    Bullet::~Bullet()
    {
    }

    void Bullet::Update(float deltaTime)
    {
        if (deadCount < 0)
        {
            isAlive = false;
        }
        else
        {
            deadCount -= deltaTime;
        }

        speed = dir * deltaTime * boost;

        pos += speed;

        // 3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        // �����蔻�胂�f���̈ʒu�X�V
        CollisionUpdate();
    }

    void Bullet::Draw()
    {
        MV1DrawModel(modelHandle);

        //DrawCollider();
    }

    void Bullet::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̃^�O���擾
        ObjectTag tag = other->GetTag();

        // ���g���v���C���[�e�ł����
        if (this->tag == ObjectTag::PlayerBullet)
        {
            // �G�l�~�[�Ƃ̓����蔻��
            if (tag == ObjectTag::Enemy)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }

        // ���g���G�l�~�[�e�ł����
        if (this->tag == ObjectTag::EnemyBullet)
        {
            // �v���C���[�Ƃ̓����蔻��
            if (tag == ObjectTag::Player)
            {
                if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
                {
                    isAlive = false;
                }
            }
        }
    }
}// namespace My3dApp