#include "UserInterface.h"
#include "DxLib.h"

namespace My3dApp
{
    UserInterface* UserInterface::instance = nullptr;

    UserInterface::UserInterface()
    {
        instance = this;
        // フォントの読み込みが成功したら
        if (AddFontResourceEx("../asset/font/851CHIKARA-DZUYOKU_kanaA_004.ttf", FR_PRIVATE, NULL) > 0)
        {
            ChangeFont("851チカラヅヨク-かなA", DX_CHARSET_DEFAULT);
        }
        // 失敗したら
        else
        {
            // エラーメッセージを表示する
            MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
        }
    }

    UserInterface::~UserInterface()
    {
        // フォントの削除が成功したら
        if (RemoveFontResourceEx("../asset/font/851CHIKARA-DZUYOKU_kanaA_004.ttf", FR_PRIVATE, NULL))
        {
            // 処理なし
        }
        // 失敗したら
        else
        {
            // エラーメッセージを表示する
            MessageBox(NULL, "remove failure", "", MB_OK);
        }
    }

    void UserInterface::CreateInstance()
    {
        if (!instance)
        {
            instance = new UserInterface();
        }
    }

    void UserInterface::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void UserInterface::UIText(int x, int y, int color, const char* str, float num)
    {
        DrawFormatString(x, y, color, str, num);
    }

    void UserInterface::UIText(int x, int y, int color, const char* str)
    {
        DrawString(x, y, str, color);
    }

    void UserInterface::UIBox(int x1, int x2, int y1, int y2, int frameSize, int mainCr, int frameCr)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

        // ベース
        DrawBox(x1, y1, x2, y2, mainCr, TRUE);

        // 上辺
        DrawLine(x1 + frameSize, y1 + frameSize / 2, x2 - frameSize, y1 + frameSize / 2, frameCr, frameSize);

        // 下辺
        DrawLine(x1 + frameSize, y2 - frameSize / 2, x2 - frameSize, y2 - frameSize / 2, frameCr, frameSize);

        // 左辺
        DrawLine(x1 + frameSize / 2, y1, x1 + frameSize / 2, y2, frameCr, frameSize);

        // 右辺
        DrawLine(x2 - frameSize / 2, y1, x2 - frameSize / 2, y2, frameCr, frameSize);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}// namespace My3dApp