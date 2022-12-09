#include "GamePad.h"

namespace My3dApp
{
    GamePad* GamePad::instance = nullptr;
    XINPUT_STATE GamePad::padState;
    bool GamePad::padInput[16] = { 0 };

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

        /** 全ボタンの入力確認*/
        for (int i = 0; i < 16; i++)
        {
            if (i < 6 || 11 < i)
            {
                if (padState.Buttons[i])
                {
                    padInput[i] = true;
                }
                else
                {
                    padInput[i] = false;
                }
            }
        }
    }
}/** namespace My3dApp*/