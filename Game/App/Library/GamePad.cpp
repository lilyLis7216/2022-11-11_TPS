#include "GamePad.h"

namespace My3dApp
{
    GamePad* GamePad::instance = nullptr;

    XINPUT_STATE GamePad::inputState;

    int GamePad::buttonBit = 0x00;

    int GamePad::buttonState[16] = { 0 };

    const unsigned int BIT_FLAG[] =
    {
        (1 << 0),   // �f�W�^�������{�^����
        (1 << 1),   // �f�W�^�������{�^����
        (1 << 2),   // �f�W�^�������{�^����
        (1 << 3),   // �f�W�^�������{�^���E
        (1 << 4),   // START�{�^��
        (1 << 5),   // BACK�{�^��
        (1 << 6),   // ���X�e�B�b�N��������
        (1 << 7),   // �E�X�e�B�b�N��������
        (1 << 8),   // LB�{�^��
        (1 << 9),   // RB�{�^��
        (1 << 10),  // ����U��Ȃ�
        (1 << 11),  // ����U��Ȃ�
        (1 << 12),  // A�{�^��
        (1 << 13),  // B�{�^��
        (1 << 14),  // X�{�^��
        (1 << 15),  // Y�{�^��
    };

    GamePad::GamePad()
    {
        instance = this;
        inputState = { 0 };
    }

    GamePad::~GamePad()
    {
    }

    void GamePad::CreateInstance()
    {
        if (!instance)
        {
            instance = new GamePad();
        }
    }

    void GamePad::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void GamePad::Update()
    {
        GetJoypadXInputState(DX_INPUT_KEY_PAD1, &inputState);

        // �S�{�^���̓��͊m�F
        for (int i = 0; i < 16; i++)
        {
            if (inputState.Buttons[i])
            {
                if (buttonBit & BIT_FLAG[i])
                {
                    buttonState[i]++;
                }
                else
                {
                    buttonBit |= BIT_FLAG[i];
                }
            }
            else
            {
                if (buttonBit & BIT_FLAG[i])
                {
                    buttonBit &= ~BIT_FLAG[i];
                    buttonState[i] = -1;
                }
                else
                {
                    buttonState[i] = 0;
                }
            }
        }
    }

    bool GamePad::GetInput(const int buttonNumber)
    {
        if (buttonBit & BIT_FLAG[buttonNumber])
        {
            return true;
        }
        return false;
    }

    int GamePad::GetButtonState(const int buttonNumber)
    {
        return buttonState[buttonNumber];
    }
}/** namespace My3dApp*/