#include "NormalEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    NormalEnemy::NormalEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        // ���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // ���f���̑傫��
        float modelSize = 0.5f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 65.0f;

        gravity = -500.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    NormalEnemy::~NormalEnemy()
    {
        // ���f���̌�n��
        AssetManager::ReleaseMesh(modelHandle);
    }

    void NormalEnemy::Update(float deltaTime)
    {
        if (isNockBack)
        {
            // �m�b�N�o�b�N����
            NockBack(deltaTime);
        }
        else
        {
            // �ړ�
            Move(deltaTime);

            shotInterval -= deltaTime;

            Shot();
        }

        gravity -= GRAVITY * deltaTime;

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

    void NormalEnemy::Move(float deltaTime)
    {
        // �v���C���[�̎擾
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // �v���C���[�̍��W���玩�g�̍��W�������Č����x�N�g�����v�Z����
        VECTOR tmp = player->GetPos() - pos;

        // �����x�N�g���̖�����
        tmp.y = 0;

        if (VSize(tmp) > 300.0f)
        {
            dir = VNorm(tmp);

            speed = (dir * deltaTime * 300.0f);

            pos += speed;
        }
        else
        {
            dir = VNorm(tmp);
        }
    }

    void NormalEnemy::NockBack(float deltaTime)
    {
        // �m�b�N�o�b�N��������𐳋K������
        nockBackDir = VNorm(nockBackDir);

        speed = (nockBackDir * 400.0f * deltaTime);

        pos += speed;
    }
}// namespace My3dApp