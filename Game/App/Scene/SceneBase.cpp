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
    * シーン確認用
    */
    void SceneBase::CheckNowScene()
    {
        DrawFormatString(100, 200, GetColor(255, 255, 255), "%s", text);
    }

    SceneBase* SceneBase::ChangeScene()
    {
        if (CheckHitKey(KEY_INPUT_1))
        {
            return new Title();
        }

        if (CheckHitKey(KEY_INPUT_2))
        {
            return new StageSelect();
        }

        if (CheckHitKey(KEY_INPUT_3))
        {
            return new Play();
        }

        if (CheckHitKey(KEY_INPUT_4))
        {
            return new Result();
        }
        return this;
    }

}/** namespace My3dApp*/