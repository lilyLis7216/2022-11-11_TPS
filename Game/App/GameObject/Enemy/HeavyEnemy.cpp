#include "HeavyEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"
#include "../Bullet/NormalBullet.h"

namespace My3dApp
{
    HeavyEnemy::HeavyEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        enemyType = 2;

        // ���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // ���f���̑傫��
        float modelSize = 1.0f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 100.0f;

        weight = 1000.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    HeavyEnemy::~HeavyEnemy()
    {
        // ���f���̌�n��
        AssetManager::ReleaseMesh(modelHandle);
    }
    void HeavyEnemy::Update(float deltaTime)
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

    void HeavyEnemy::Move(float deltaTime)
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
            speed = (dir * deltaTime * 100.0f);

            pos += speed;

            canShot = false;
        }
        else if (VSize(tmp) > 300.0f)
        {
            speed = (dir * deltaTime * 100.0f);

            pos += speed;

            canShot = true;
        }
    }

    void HeavyEnemy::Shot(float deltaTime)
    {
        shotInterval -= deltaTime;
        if (shotInterval < 0)
        {
            shotInterval = 5.0f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::EnemyBulletL, pos, dir));
        }
    }
}// namespace My3dApp