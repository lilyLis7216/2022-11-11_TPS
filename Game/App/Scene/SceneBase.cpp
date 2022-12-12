#include "SceneBase.h"
#include "DxLib.h"
#include "Title.h"
#include "StageSelect.h"
#include "Play.h"
#include "Result.h"

namespace My3dApp
{
    SceneBase::SceneBase()
        : text(nullptr)
    {
        // èàóùÇ»Çµ
    }

    SceneBase::~SceneBase()
    {
        // èàóùÇ»Çµ
    }

    SceneBase* SceneBase::CheckRetScene(int sceneNum)
    {
        if (CheckHitKey(KEY_INPUT_1) && sceneNum != 1)
        {
            return new Title();
        }

        if (CheckHitKey(KEY_INPUT_2) && sceneNum != 2)
        {
            return new StageSelect();
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
        DrawFormatString(10, 10, GetColor(255, 255, 255), "%s", text);
    }
}// namespace My3dApp