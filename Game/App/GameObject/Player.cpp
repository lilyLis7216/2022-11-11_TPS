#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameObjectManager.h"
#include "EffekseerForDXLib.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "Bullet/NormalBullet.h"
#include "Bullet/ChargeBullet.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , isRotate(false)
        , shotInterval(0)
        , isCharge(false)
    {
        // 3Dモデルの読み込み
        modelHandle = AssetManager::GetMesh("../asset/model/player.mv1");

        // 座標の初期化
        pos = VGet(0, 100, 0);

        // 座標の設定
        MV1SetPosition(modelHandle, pos);

        // 大きさの設定
        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        // 向きの初期化
        dir = VGet(1, 0, 0);

        // 目標向きの初期化
        aimDir = dir;

        // 速度の初期化
        speed = VGet(0, 0, 0);

        // 当たり判定種類を球体に設定
        collisionType = CollisionType::Sphere;

        // 当たり判定球のローカル中心座標を初期化
        collisionSphere.localCenter = VGet(0, 0, 0);

        // 当たり判定球の半径を初期化
        collisionSphere.radius = 65.0f;

        // 線分当たり判定を設定
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // 当たり判定の更新
        CollisionUpdate();
    }

    Player::~Player()
    {
        // モデルのアンロード
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Player::Update(float deltaTime)
    {
        Move(deltaTime);

        RotateCheck();

        shotInterval -= deltaTime;

        Shot();

        CollisionUpdate();
    }

    void Player::Draw()
    {
        // 3Dモデルの描画
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Player::OnCollisionEnter(const GameObject* other)
    {
        // 調べるオブジェクトのタグを取得
        ObjectTag tag = other->GetTag();

        // マップとの衝突
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // マップと自身の境界球との当たり判定
            MV1_COLL_RESULT_POLY_DIM collInfo;

            // 当たっている場合
            if (CollisionPair(collisionSphere, collModel, collInfo))
            {
                // 押し戻し量
                VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(collisionSphere, collInfo);

                // 押し戻し
                pos += pushBackVec;

                onGround = true;

                // 当たり判定情報の解放
                MV1CollResultPolyDimTerminate(collInfo);

                // 当たり判定の更新
                CollisionUpdate();
            }
            else
            {
                onGround = false;

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

        // 敵との衝突
        if (tag == ObjectTag::Enemy)
        {
            // 当たっていたら
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // 差分を計算して
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // 押し戻し量を計算する
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // 正規化して
                    pushBack = VNorm(pushBack);

                    pushBack.y = 1;

                    // 押し戻す
                    pos += pushBack * -dif;
                }
                // 当たり判定の更新
                CollisionUpdate();
            }
        }

        if (tag == ObjectTag::EnemyBullet)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // 差分を計算して
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // 押し戻し量を計算する
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // 正規化して
                    pushBack = VNorm(pushBack);

                    // 押し戻す
                    pos += pushBack * -dif * 100.0f;
                }

                // 当たり判定の更新
                CollisionUpdate();
            }
        }
    }

    void Player::Move(float deltaTime)
    {
        // カメラを持ってくる
        GameObject* camera = GameObjectManager::GetFirstGameObject(ObjectTag::Camera);

        // カメラの正面方向の位置ベクトルを計算
        VECTOR front = pos - camera->GetPos();

        // 高さ無効
        front.y = 0.0f;

        // ベクトルの正規化
        front = VNorm(front);

        // Y軸ベクトル
        VECTOR YAxis = { 0,1,0 };

        // 上方向
        VECTOR UP = front;

        // 下方向
        VECTOR DOWN = VScale(front, -1.0f);

        // 右方向
        VECTOR RIGHT = VCross(YAxis, front);

        // 左方向
        VECTOR LEFT = VScale(RIGHT, -1.0f);

        // 移動用ベクトル
        VECTOR inputVec = VGet(0, 0, 0);

        // 入力があったかどうか
        bool input = false;

        if (GamePad::GetInput(Button::UP) || 0 < GamePad::GetLeftStickY() || CheckHitKey(KEY_INPUT_W))
        {
            inputVec += UP;
            input = true;
        }

        if (GamePad::GetInput(Button::DOWN) || GamePad::GetLeftStickY() < 0 || CheckHitKey(KEY_INPUT_S))
        {
            inputVec += DOWN;
            input = true;
        }

        if (GamePad::GetInput(Button::LEFT) || GamePad::GetLeftStickX() < 0 || CheckHitKey(KEY_INPUT_A))
        {
            inputVec += LEFT;
            input = true;
        }

        if (GamePad::GetInput(Button::RIGHT) || 0 < GamePad::GetLeftStickX() || CheckHitKey(KEY_INPUT_D))
        {
            inputVec += RIGHT;
            input = true;
        }

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

            speed = inputVec + (inputVec * deltaTime * 400.0f);
        }
        else
        {
            speed *= 0.9f;
        }

        pos += speed;

        if (!onGround)
        {
            speed = (VGet(0, -1, 0) * 10.0f);
        }

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

    void Player::RotateCheck()
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

    void Player::Shot()
    {
        if (CheckHitKey(KEY_INPUT_J) && !CheckHitKey(KEY_INPUT_K) && shotInterval < 0)
        {
            shotInterval = 0.25f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::PlayerBullet, pos, dir));
        }

        if (CheckHitKey(KEY_INPUT_K) && !CheckHitKey(KEY_INPUT_J) && !isCharge)
        {
            isCharge = true;
            GameObjectManager::Entry(new ChargeBullet(ObjectTag::PlayerBullet, pos, dir));
        }

        if (!CheckHitKey(KEY_INPUT_K))
        {
            isCharge = false;
        }
    }
}// namespace My3dApp