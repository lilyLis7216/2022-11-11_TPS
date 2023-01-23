#include "Map.h"
#include "ObjectTag.h"
#include "../Manager/AssetManager.h"
#include "../Library/Calc3D.h"

namespace My3dApp
{
    Map::Map()
        : GameObject(ObjectTag::Map)
    {
        ModelLoad();
    }

    Map::Map(VECTOR pos)
        : GameObject(ObjectTag::Map, pos)
    {
        ModelLoad();
    }

    Map::~Map()
    {
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Map::ModelLoad()
    {
        // �\���p���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/map/stage.mv1");

        // �\�����f���̃X�P�[�����O
        MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));

        // �\�����f���̈ʒu�Z�b�g
        MV1SetPosition(modelHandle, pos);

        // �����蔻��p���f���̓ǂݍ���
        collisionModel = AssetManager::GetMesh("../asset/model/map/stage.mv1");

        MV1SetScale(collisionModel, VGet(1.0f, 1.0f, 1.0f));

        // �����蔻�胂�f���ɕs�����x��ݒ�
        MV1SetOpacityRate(collisionModel, 0.3f);

        // �\�����f���Ɠ����蔻�胂�f���̈ʒu�������
        MV1SetPosition(collisionModel, pos + VGet(-45, 0, -35));

        // ���f���̓����蔻����̍č\�z
        MV1SetupCollInfo(collisionModel);
    }

    void Map::Update(float deltaTime)
    {
        // �����Ȃ�
    }

    void Map::Draw()
    {
        MV1DrawModel(modelHandle);

        DrawCollider();
    }
}// namespace My3dApp