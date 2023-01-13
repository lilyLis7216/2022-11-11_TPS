#include "Enemy.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/AnimationController.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "ObjectTag.h"

namespace My3dApp
{
    Enemy::Enemy()
        : Enemy(initPos)
    {
    }

    Enemy::Enemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , animCtrl(nullptr)
        , animTypeID(0)
        , isRotate(false)
        , moveCount(10.0f)
        , isMove(false)
        , moveTmp(0)
    {
        modelHandle = AssetManager::GetMesh("../asset/model/test/enemy.mv1");

        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        dir = VGet(1, 0, 0);

        aimDir = dir;

        speed = VGet(0, 0, 0);

        collisionType = CollisionType::Sphere;

        collisionSphere.localCenter = VGet(0, 50.0f, 0);

        collisionSphere.radius = 30.0f;

        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));
    }

    Enemy::~Enemy()
    {
        // モデルのアンロード
        AssetManager::ReleaseMesh(modelHandle);

        // アニメーションコントローラの削除
        delete animCtrl;
    }

    void Enemy::Update(float deltaTime)
    {
        Move(deltaTime);

        RotateCheck();
    }

    void Enemy::Draw()
    {
        // モデルの描画
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Enemy::OnCollisionEnter(const GameObject* other)
    {
        // 調べるオブジェクトのタグを取得
        ObjectTag tag = other->GetTag();

        // マップとの衝突
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // マップと自身の境界旧都の当たり判定
            MV1_COLL_RESULT_POLY_DIM collInfo;

            // 当たっている場合
            if (CollisionPair(collisionSphere, collModel, collInfo))
            {
                // 押し戻し量
                VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(collisionSphere, collInfo);

                // 押し戻し
                pos += pushBackVec;

                // 当たり判定情報の解放
                MV1CollResultPolyDimTerminate(collInfo);

                // 当たり判定の更新
                CollisionUpdate();
            }

            // 背景と足元線分当たり判定
            MV1_COLL_RESULT_POLY collInfoLine;

            // 当たっている場合
            if (CollisionPair(collisionLine, collModel, collInfoLine))
            {
                // 足元を衝突点に合わせる
                pos = collInfoLine.HitPosition;

                // 当たり判定の更新
                CollisionUpdate();
            }
        }
    }

    void Enemy::Move(float deltaTime)
    {
        // プレイヤーの取得
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // プレイヤーの座標から自身の座標を引いて向きベクトルを計算する
        VECTOR tmp = player->GetPos() - pos;

        // 高さベクトルの無効化
        tmp.y = 0;

        // 移動用ベクトル
        VECTOR inputVec = VGet(0, 0, 0);

        // 入力があったかどうか
        bool input = false;

        if (abs(tmp.x) < 200.0f)
        {
            input = true;
        }

        if (abs(tmp.z) < 200.0f)
        {
            input = true;
        }

        inputVec += tmp;

        // 入力があったら
        if (input)
        {
            // 左右上下同時押しなどで入力ベクトルが0のとき
            if (VSquareSize(inputVec) < 0.5f)
            {
                return;
            }

            // 方向を正規化
            inputVec = VNorm(inputVec);

            // 入力方向は現在向いている方向と異なるか
            if (IsNearAngle(inputVec, dir))
            {
                dir = inputVec;
            }
            else
            {
                isRotate = true;
                aimDir = inputVec;
            }

            speed = inputVec + (inputVec * deltaTime * 100.0f);

            // もし他のモーション中だったら走りモーションへ
            if (animTypeID != 1)
            {
                animTypeID = 1;
                //animCtrl->StartAnimation(animTypeID);
            }
        }
        else
        {
            speed *= 0.9f;

            // もしほかのモーション中だったら歩きモーションへ
            if (animTypeID != 0)
            {
                animTypeID = 0;
                //animCtrl->StartAnimation(animTypeID);
            }
        }

        pos += speed;

        // 3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        // 向きに合わせてモデルを回転
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // 当たり判定モデルの位置更新
        CollisionUpdate();
    }

    void Enemy::RotateCheck()
    {
        if (isRotate)
        {
            // 回転が目標角度に十分近ければ回転終了
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                isRotate = false;
            }
            else
            {
                // 回転させる
                VECTOR interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);

                // 回転が目標角度を超えていないか
                VECTOR cross1 = VCross(dir, aimDir);
                VECTOR cross2 = VCross(interPolateDir, aimDir);

                // 目標角度を超えたら終了
                if (cross1.y * cross2.y < 0.0f)
                {
                    interPolateDir = aimDir;
                    isRotate = false;
                }

                // 目標ベクトルに10度だけ近づけた角度
                dir = interPolateDir;
            }
        }
    }
}// namespace My3dApp