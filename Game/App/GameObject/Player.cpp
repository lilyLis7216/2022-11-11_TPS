#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../Library/Calc3D.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , animTypeID(0)
        , isRotate(false)
        , padInputState(0)
        , stickX(0)
        , stickY(0)
    {

        /** 3Dモデルの読み込み*/
        modelHandle = AssetManager::GetMesh("../Assets/model/player2/unityChanModel.mv1");

        MV1SetScale(modelHandle, VGet(0.01f, 0.01f, 0.01f));

        pos = VGet(0, 0, 0);

        dir = VGet(1, 0, 0);

        aimDir = dir;

        speed = VGet(0, 0, 0);
    }

    Player::~Player()
    {
        /** モデルのアンロード*/
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Player::Update(float deltaTime)
    {
        InputCheck();

        Move(deltaTime);
    }

    void Player::Draw()
    {
        /** 3Dモデルの描画*/
        MV1DrawModel(modelHandle);
    }

    void Player::InputCheck()
    {
        /** パッドの入力を取得*/
        padInputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

        /** アナログスティックの入力を取得*/
        GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_KEY_PAD1);
    }

    void Player::Move(float deltaTime)
    {
        /** 左方向*/
        VECTOR LEFT = { -1, 0, 0 };

        /** 右方向*/
        VECTOR RIGHT = { 1, 0, 0 };

        /** 上方向*/
        VECTOR UP = { 0, 0, 1 };

        /** 下方向*/
        VECTOR DOWN = { 0, 0, -1 };

        /** 移動用ベクトル*/
        VECTOR inputVec = VGet(0, 0, 0);

        /** 入力があったかどうか*/
        bool input = false;

        if (0 < stickX || padInputState & PAD_INPUT_RIGHT)
        {
            inputVec += RIGHT;
            input = true;
        }

        if (stickX > 0 || padInputState & PAD_INPUT_LEFT)
        {
            inputVec += LEFT;
            input = true;
        }

        if (0 < stickY || padInputState & PAD_INPUT_DOWN)
        {
            inputVec += DOWN;
            input = true;
        }

        if (stickY < 0 || padInputState & PAD_INPUT_UP)
        {
            inputVec += UP;
            input = true;
        }

        /** 入力があったら*/
        if (input)
        {
            /** 左右上下同時押しなどで入力ベクトルが0のとき*/
            if (VSquareSize(inputVec) < 0.5f)
            {
                return;
            }

            /** 方向を正規化*/
            inputVec = VNorm(inputVec);

            /** 入力方向は現在向いている方向と異なるか？*/
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
        }
        else
        {
            speed *= 0.9f;
        }

        pos += speed;

        /** 3Dモデルのポジション設定*/
        MV1SetPosition(modelHandle, pos);

        /** 向きに合わせてモデルを回転*/
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        VECTOR negativeVec = VTransform(dir, rotYMat);

        /** モデルに回転をセットする*/
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    }

}/** namespace My3dApp*/