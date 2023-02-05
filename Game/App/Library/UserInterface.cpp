#include "UserInterface.h"
#include "DxLib.h"

namespace My3dApp
{
    UserInterface* UserInterface::instance = nullptr;

    UserInterface::UserInterface()
    {
        instance = this;
    }

    UserInterface::~UserInterface()
    {
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

    void UserInterface::UIText(int x, int y, int color, const char* str, int num)
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
        DrawLine(x1, y1 + frameSize / 2, x2, y1 + frameSize / 2, frameCr, frameSize);

        // 下辺
        DrawLine(x1, y2 - frameSize / 2, x2, y2 - frameSize / 2, frameCr, frameSize);

        // 左辺
        DrawLine(x1 + frameSize / 2, y1, x1 + frameSize / 2, y2, frameCr, frameSize);

        // 右辺
        DrawLine(x2 - frameSize / 2, y1, x2 - frameSize / 2, y2, frameCr, frameSize);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}// namespace My3dApp