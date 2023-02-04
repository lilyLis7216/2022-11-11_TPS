#pragma once

#include "DxLib.h"

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// ゲームパッドクラス
    /// </summary>
    class GamePad final
    {
    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        GamePad();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~GamePad();

        // ゲームパッドクラスの唯一のインスタンス
        static GamePad* instance;

        // パッドの入力状態
        static XINPUT_STATE inputState;

        // ボタンの入力ビット
        static int buttonBit;

        // 
        static int buttonState[16];

    public:
        /// <summary>
        /// インスタンスの生成
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// インスタンスの削除
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// ゲームパッドの更新
        /// </summary>
        static void Update();

        // ボタンの列挙型（マジックナンバー回避用）
        enum ButtonNum
        {
            UP = 0,  // デジタル方向ボタン上
            DOWN,    // デジタル方向ボタン下
            LEFT,    // デジタル方向ボタン左
            RIGHT,   // デジタル方向ボタン右
            START,   // STARTボタン
            BACK,    // BACKボタン
            LSTICK,  // 左スティック押し込み
            RSTICK,  // 右スティック押し込み
            LB,      // LBボタン
            RB,      // RBボタン
            NONE1,   // 割り振りなし
            NONE2,   // 割り振りなし
            A,       // Aボタン
            B,       // Bボタン
            X,       // Xボタン
            Y,       // Yボタン
        };

        /// <summary>
        /// ボタンの入力状態の取得
        /// </summary>
        /// <param name="buttonNumber">取得したいボタン</param>
        /// <returns>入力されていたらtrue そうでなければfalse</returns>
        static bool GetInput(const int buttonNumber);

        /// <summary>
        /// ボタンの状態取得
        /// </summary>
        /// <param name="buttonNumber">取得したいボタン</param>
        /// <returns>0:押されていない 1:押された瞬間 2～:押しっぱなし -1:離した瞬間</returns>
        static int GetButtonState(const int buttonNumber);

        /// <summary>
        /// 左トリガーの取得
        /// </summary>
        /// <returns></returns>
        static const unsigned char GetLeftTrigger() { return inputState.LeftTrigger; }

        /// <summary>
        /// 右トリガーの取得
        /// </summary>
        /// <returns></returns>
        static const unsigned char GetRightTrigger() { return inputState.RightTrigger; }

        /// <summary>
        /// 左スティックのX座標
        /// </summary>
        /// <returns></returns>
        static const short GetLeftStickX() { return inputState.ThumbLX; }

        /// <summary>
        /// 左スティックのY座標
        /// </summary>
        /// <returns></returns>
        static const short GetLeftStickY() { return inputState.ThumbLY; }

        /// <summary>
        /// 右スティックのX座標
        /// </summary>
        /// <returns></returns>
        static const short GetRightStickX() { return inputState.ThumbRX; }

        /// <summary>
        /// 右スティックのY座標
        /// </summary>
        /// <returns></returns>
        static const short GetRightStickY() { return inputState.ThumbRY; }
    };

#define Button GamePad::ButtonNum
}/** namespace My3dApp*/