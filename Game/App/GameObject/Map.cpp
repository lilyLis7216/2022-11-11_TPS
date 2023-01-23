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
        // 表示用モデルの読み込み
        modelHandle = AssetManager::GetMesh("../asset/model/map/stage.mv1");

        // 表示モデルのスケーリング
        MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));

        // 表示モデルの位置セット
        MV1SetPosition(modelHandle, pos);

        // 当たり判定用モデルの読み込み
        collisionModel = AssetManager::GetMesh("../asset/model/map/stage.mv1");

        MV1SetScale(collisionModel, VGet(1.0f, 1.0f, 1.0f));

        // 当たり判定モデルに不透明度を設定
        MV1SetOpacityRate(collisionModel, 0.3f);

        // 表示モデルと当たり判定モデルの位置を微調整
        MV1SetPosition(collisionModel, pos + VGet(-45, 0, -35));

        // モデルの当たり判定情報の再構築
        MV1SetupCollInfo(collisionModel);
    }

    void Map::Update(float deltaTime)
    {
        // 処理なし
    }

    void Map::Draw()
    {
        MV1DrawModel(modelHandle);

        DrawCollider();
    }
}// namespace My3dApp