#include "GamePad.h"

namespace My3dApp
{
    GamePad* GamePad::instance = nullptr;

    XINPUT_STATE GamePad::padState;

    int GamePad::buttonInput = 0x00;

    const unsigned int BIT_FLAG[] =
    {
        (1 << 0),   // デジタル方向ボタン上
        (1 << 1),   // デジタル方向ボタン下
        (1 << 2),   // デジタル方向ボタン左
        (1 << 3),   // デジタル方向ボタン右
        (1 << 4),   // STARTボタン
        (1 << 5),   // BACKボタン
        (1 << 6),   // 左スティック押し込み
        (1 << 7),   // 右スティック押し込み
        (1 << 8),   // LBボタン
        (1 << 9),   // RBボタン
        (1 << 10),  // 割り振りなし
        (1 << 11),  // 割り振りなし
        (1 << 12),  // Aボタン
        (1 << 13),  // Bボタン
        (1 << 14),  // Xボタン
        (1 << 15),  // Yボタン
    };

    GamePad::GamePad()
    {
        instance = this;
        padState = { 0 };
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
        GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padState);

        // 全ボタンの入力確認
        for (int i = 0; i < 16; i++)
        {
            if (padState.Buttons[i])
            {
                buttonInput |= (1 << BIT_FLAG[i]);
            }
            else
            {
                buttonInput &= ~(1 << BIT_FLAG[i]);
            }
        }
    }

    bool GamePad::GetInput(const int buttonNumber)
    {
        if (buttonInput & (1 << BIT_FLAG[buttonNumber]))
        {
            return true;
        }
        return false;
    }
}/** namespace My3dApp*/