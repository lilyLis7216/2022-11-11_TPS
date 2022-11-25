#pragma once

namespace My3dApp
{
    /**
    * シーンの基底クラス
    * 純粋仮想関数を持っている抽象クラス
    */
    class SceneBase
    {
    protected:
        /** シーンの表記用テキスト*/
        const char* text;

    public:
        /** コンストラクタ*/
        SceneBase();

        /** 仮想デストラクタ*/
        virtual ~SceneBase();

        /** シーンの更新（純粋仮想関数）*/
        virtual SceneBase* Update() = 0;

        /** シーンの描画（純粋仮想関数）*/
        virtual void Draw() = 0;

        /**
        * 以下デバッグ用関数
        */

        /** 現在のシーンの確認関数*/
        void CheckNowScene();

        SceneBase* ChangeScene();

    };

}/** namespace My3dApp*/