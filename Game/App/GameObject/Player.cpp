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

        /** 3D���f���̓ǂݍ���*/
        modelHandle = AssetManager::GetMesh("");

        MV1SetScale(modelHandle, VGet(0.01f, 0.01f, 0.01f));

        pos = VGet(0, 0, 0);

        dir = VGet(1, 0, 0);

        aimDir = dir;

        speed = VGet(0, 0, 0);
    }

    Player::~Player()
    {
        /** ���f���̃A�����[�h*/
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Player::Update(float deltaTime)
    {
        InputCheck();

        Move(deltaTime);
    }

    void Player::Draw()
    {
        /** 3D���f���̕`��*/
        MV1DrawModel(modelHandle);
    }

    void Player::InputCheck()
    {
        /** �p�b�h�̓��͂��擾*/
        padInputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

        /** �A�i���O�X�e�B�b�N�̓��͂��擾*/
        GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_KEY_PAD1);
    }

    void Player::Move(float deltaTime)
    {
        /** ������*/
        VECTOR LEFT = { -1, 0, 0 };

        /** �E����*/
        VECTOR RIGHT = { 1, 0, 0 };

        /** �����*/
        VECTOR UP = { 0, 0, 1 };

        /** ������*/
        VECTOR DOWN = { 0, 0, -1 };

        /** �ړ��p�x�N�g��*/
        VECTOR inputVec = VGet(0, 0, 0);

        /** ���͂����������ǂ���*/
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