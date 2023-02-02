#include "NormalEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    NormalEnemy::NormalEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        // モデルの読み込み
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // 座標の設定
        MV1SetPosition(modelHandle, this->pos);

        // モデルの大きさ
        float modelSize = 0.5f;

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // 当たり判定球の半径の設定
        collisionSphere.radius = 65.0f;

        gravity = -500.0f;

        // 当たり判定の更新
        CollisionUpdate();
    }

    NormalEnemy::~NormalEnemy()
    {
        // モデルの後始末
        AssetManager::ReleaseMesh(modelHandle);
    }

    void NormalEnemy::Update(float deltaTime)
    {
        if (isNockBack)
        {
            // ノックバック処理
            NockBack(deltaTime);
        }
        else
        {
            // 移動
            Move(deltaTime);

            shotInterval -= deltaTime;

            Shot();
        }

        gravity -= GRAVITY * deltaTime;

        pos.y += gravity * deltaTime;

        // 向きに合わせてモデルを回転
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // 3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        // 当たり判定モデルの位置更新
        CollisionUpdate();

        if (IsDead())
        {
            isAlive = false;
        }
    }

    void NormalEnemy::Move(float deltaTime)
    {
        // プレイヤーの取得
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // プレイヤーの座標から自身の座標を引いて向きベクトルを計算する
        VECTOR tmp = player->GetPos() - pos;

        // 高さベクトルの無効化
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
        // ノックバックする向きを正規化して
        nockBackDir = VNorm(nockBackDir);

        speed = (nockBackDir * 400.0f * deltaTime);

        pos += speed;
    }
}// namespace My3dApp