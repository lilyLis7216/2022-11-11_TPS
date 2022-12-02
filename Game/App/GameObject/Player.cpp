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

        /** 3D���f���̓ǂݍ���*/
        modelHandle = AssetManager::GetMesh("../Assets/model/player2/unityChanModel.mv1");

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

        /** ���͂���������*/
        if (input)
        {
            /** ���E�㉺���������Ȃǂœ��̓x�N�g����0�̂Ƃ�*/
            if (VSquareSize(inputVec) < 0.5f)
            {
                return;
            }

            /** �����𐳋K��*/
            inputVec = VNorm(inputVec);

            /** ���͕����͌��݌����Ă�������ƈقȂ邩�H*/
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

        /** 3D���f���̃|�W�V�����ݒ�*/
        MV1SetPosition(modelHandle, pos);

        /** �����ɍ��킹�ă��f������]*/
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        VECTOR negativeVec = VTransform(dir, rotYMat);

        /** ���f���ɉ�]���Z�b�g����*/
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    }

}/** namespace My3dApp*/