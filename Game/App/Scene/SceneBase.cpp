#include "SceneBase.h"
#include "DxLib.h"
#include "Title.h"
#include "StageSelect.h"
#include "Play.h"
#include "Result.h"

namespace My3dApp
{
    /**
    * コンストラクタ
    */
    SceneBase::SceneBase()
        : text(nullptr)
    {
        /** 処理なし*/
    }

    /**
    * 仮想デストラクタ
    */
    SceneBase::~SceneBase()
    {
        /** 処理なし*/
    }

    /**
    * シーンの切り替え入力
    */
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

    /**
    * シーン確認用
    */
    void SceneBase::CheckNowScene()
    {
        DrawFormatString(10, 10, GetColor(255, 255, 255), "%s", text);
    }
}/** namespace My3dApp*/