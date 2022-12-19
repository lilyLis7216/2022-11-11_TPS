#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../Library/AnimationController.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , animCtrl(nullptr)
        , animTypeID(0)
        , isRotate(false)
    {

        // 3Dモデルの読み込み
        modelHandle = AssetManager::GetMesh("../Assets/Model/test/player.mv1");

        // モデルの大きさ設定
        MV1SetScale(modelHandle, VGet(1, 1, 1));

        //// アニメーションコントローラの生成
        //animCtrl = new AnimationController(modelHandle);

        //// 待機アニメーションの読み込み
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimIdle.mv1");

        //// 走行アニメーションの読み込み
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimRun.mv1");

        //// 攻撃アニメーションの読み込み
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimPunch.mv1");

        //// 初期再生アニメーションの初期化
        //animCtrl->StartAnimation(animTypeID);

        // 座標の初期化
        pos = VGet(0, 0, 0);

        // 向きの初期化
        dir = VGet(1, 0, 0);

        aimDir = dir;

        // 速度の初期化
        speed = VGet(0, 0, 0);

        // 当たり判定種類を球体に設定
        collisionType = CollisionType::Sphere;

        // ローカルセンターを50
        collisionSphere.localCenter = VGet(0, 50.0f, 0);

        // 半径を30
        collisionSphere.radius = 30.0f;

        // 線分当たり判定を設定
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));
    }

    Player::~Player()
    {
        // モデルのアンロード
        AssetManager::ReleaseMesh(modelHandle);

        // アニメーションコントローラの削除
        delete animCtrl;
    }

    void Player::Update(float deltaTime)
    {
        //animCtrl->AddAnimationTime(deltaTime);

        RotateCheck();

        Move(deltaTime);

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

        // 敵との衝突
        if (tag == ObjectTag::Enemy)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                printfDx("Hit!");
            }
        }
    }

    void Player::Move(float deltaTime)
    {
        // カメラを持ってくる
        GameObject* camera = GameObjectManager::GetFirstGameObject(ObjectTag::Camera);

        // カメラの正面方向の位置ベクトルを計算
        VECTOR front = pos - camera->GetPos();

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

        if (GamePad::GetInput(Button::UP) || 0 < GamePad::GetLeftStickY())
        {
            inputVec += UP;
            input = true;
        }

        if (GamePad::GetInput(Button::DOWN) || GamePad::GetLeftStickY() < 0)
        {
            inputVec += DOWN;
            input = true;
        }

        if (GamePad::GetInput(Button::LEFT) || GamePad::GetLeftStickX() < 0)
        {
            inputVec += LEFT;
            input = true;
        }

        if (GamePad::GetInput(Button::RIGHT) || 0 < GamePad::GetLeftStickX())
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

            speed = inputVec + (inputVec * deltaTime * 200.0f);

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
}// namespace My3dApp