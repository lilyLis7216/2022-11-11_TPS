#include "Player.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , stickX(0)
        , stickY(0)
    {

        /** 3Dモデルの読み込み*/
        modelHandle = AssetManager::ProcureMesh("");

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
    }

    void Player::Draw()
    {
        /** 3Dモデルの描画*/
        MV1DrawModel(modelHandle);
    }

    void Player::InputCheck()
    {
        GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_KEY_PAD1);
    }

    void Player::Move()
    {
        /** 左方向*/
        VECTOR LEFT = { -1, 0, 0 };

        /** 右方向*/
        VECTOR RIGHT = { 1, 0, 0 };

        /** 上方向*/
        VECTOR UP = { 0, 0, 1 };

        /** 下方向*/
        VECTOR DOWN = { 0, 0, -1 };

        if (0 < stickX)
        {

        }

        if (stickX > 0)
        {

        }

        if (0 < stickY)
        {

        }

        if (stickY < 0)
        {

        }
    }

}/** namespace My3dApp*/