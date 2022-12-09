#pragma once

#include "DxLib.h"

namespace My3dApp
{
    class GamePad final
    {
    private:
        /** コンストラクタ*/
        GamePad();

        /** デストラクタ*/
        ~GamePad();

        /** ゲームパッドのインスタンス*/
        static GamePad* instance;

        /** パッドの入力状態*/
        static XINPUT_STATE padState;

        static bool padInput[16];

    public:
        static void CreateInstance();
        static void DeleteInstance();
        static void Update();

        static bool GetUp() { return padInput[0]; }
        static bool GetDown() { return padInput[1]; }
        static bool GetLeft() { return padInput[2]; }
        static bool GetRight() { return padInput[3]; }
        static bool GetStart() { return padInput[4]; }
        static bool GetBack() { return padInput[5]; }
        static bool GetButtonA() { return padInput[12]; }
        static bool GetButtonB() { return padInput[13]; }
        static bool GetButtonX() { return padInput[14]; }
        static bool GetButtonY() { return padInput[15]; }
    };
}/** namespace My3dApp*/