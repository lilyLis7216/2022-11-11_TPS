#pragma once

namespace My3dApp
{
    class UserInterface final
    {
    private:
        UserInterface();
        ~UserInterface();

        static UserInterface* instance;

    public:
        static void CreateInstance();
        static void DeleteInstance();
        static void UIText(int x, int y, int color, const char* str, float num);
        static void UIText(int x, int y, int color, const char* str);
        static void UIBox(int x1, int x2, int y1, int y2, int frameSize, int mainCr, int frameCr);
    };
}