#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../MyLib/Calc3D.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , padInputState(0)
        , stickX(0)
        , stickY(0)
    {

        /** 3Dモデルの読み込み*/
        modelHandle = AssetManager::GetMesh("");

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

        if (0 < stickX)
        {
            inputVec += RIGHT;
            input = true;
        }

        if (stickX > 0)
        {
            inputVec += LEFT;
            input = true;
        }

        if (0 < stickY)
        {
            inputVec += DOWN;
            input = true;
        }

        if (stickY < 0)
        {
            inputVec += UP;
            input = true;
        }
    }

}/** namespace My3dApp*/