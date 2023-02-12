#include "LightEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"
#include "../Bullet/NormalBullet.h"

namespace My3dApp
{
    LightEnemy::LightEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        enemyType = 1;

        // ���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // ���f���̑傫��
        float modelSize = 0.25f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 32.5f;

        weight = 500.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    LightEnemy::~LightEnemy()
    {
        // ���f���̌�n��
        AssetManager::ReleaseMesh(modelHandle);
    }

    void LightEnemy::Update(float deltaTime)
    {
        if (isNockBack)
        {
            // �m�b�N�o�b�N����
            KnockBack(deltaTime);
        }
        else
        {
            // �ړ�
            Move(deltaTime);

            if (canShot)
            {
                // �ˌ�
                Shot(deltaTime);
            }
        }

        gravity -= weight * deltaTime;

        pos.y += gravity * deltaTime;

        // �����ɍ��킹�ă��f������]
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // ���f���ɉ�]���Z�b�g����
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // 3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        // �����蔻�胂�f���̈ʒu�X�V
        CollisionUpdate();

        if (IsDead())
        {
            isAlive = false;
        }
    }

    void LightEnemy::Move(float deltaTime)
    {
        // �v���C���[�̎擾
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // �v���C���[�̍��W���玩�g�̍��W�������Č����x�N�g�����v�Z����
        VECTOR tmp = player->GetPos() - pos;

        // �����x�N�g���̖�����
        tmp.y = 0;

        dir = VNorm(tmp);

        if (VSize(tmp) > 1000.0f)
        {
            speed = (dir * deltaTime * 300.0f);

            pos += speed;

            canShot = false;
        }
        else if (VSize(tmp) > 300.0f)
        {
            speed = (dir * deltaTime * 300.0f);

            pos += speed;

            canShot = true;
        }
    }

    void LightEnemy::Shot(float deltaTime)
    {
        shotInterval -= deltaTime;
        if (shotInterval < 0)
        {
            shotInterval = 5.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBulletS, pos, dir));
        }
    }
}// namespace My3dApp