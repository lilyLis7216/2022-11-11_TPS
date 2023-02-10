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
}// namespace My3dApp