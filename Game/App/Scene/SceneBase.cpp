#include "SceneBase.h"
#include "DxLib.h"
#include "Title.h"
#include "Explanation.h"
#include "Play.h"
#include "Result.h"

namespace My3dApp
{
    SceneBase::SceneBase()
        : text(nullptr)
        , bgImage(-1)
        , nextScene(-1)
        , alpha(0)
        , fadeState(FADE_NONE)
    {
        // èàóùÇ»Çµ
    }

    SceneBase::~SceneBase()
    {
        if (bgImage != -1)
        {
            bgImage = -1;
        }
    }

    SceneBase* SceneBase::CheckRetScene(int sceneNum)
    {
        if (CheckHitKey(KEY_INPUT_1) && sceneNum != 1)
        {
            return new Title();
        }

        if (CheckHitKey(KEY_INPUT_2) && sceneNum != 2)
        {
            return new Explanation();
        }

        if (CheckHitKey(KEY_INPUT_3) && sceneNum != 3)
        {
            return new Play();
        }

        if (CheckHitKey(KEY_INPUT_4) && sceneNum != 4)
        {
            return new Result();
        }

        return this;
    }

    void SceneBase::CheckNowScene()
    {
        SetFontSize(25);
        DrawFormatString(10, 10, GetColor(255, 255, 255), "%s", text);
    }

    void SceneBase::FadeIn()
    {
        alpha -= fadeSpeed;
        if (alpha <= 0)alpha = 0;
    }

    void SceneBase::FadeOut()
    {
        alpha += fadeSpeed;
        if (alpha >= 255)alpha = 255;
    }
}// namespace My3dApp