#pragma once

namespace My3dApp
{
    /** シーンの種類*/
    enum class SceneType
    {
        Scene_Title,
        Scene_StageSelect,
        Scene_Play,
        Scene_Result,
        Scene_Exit, 
    };

    /**
    * シーンの基底クラス
    * 純粋仮想関数を持っている抽象クラス
    */
    class SceneBase
    {
    protected:
        /** 現在のシーンの種類*/
        SceneType nowSceneType;

        /** シーンの表記用テキスト*/
        const char* text;

    public:
        /**
        * コンストラクタ
        * 
        * @param[in] sceneType シーンの種類
        */
        SceneBase(SceneType sceneType);

        /** 仮想デストラクタ*/
        virtual ~SceneBase();

        /**
        * 更新処理（純粋仮想関数）
        * 
        * @return シーンの種類
        */
        virtual SceneType Update() = 0;

        /** 描画処理（純粋仮想関数）*/
        virtual void Draw() = 0;

        /**
        * 以下デバッグ用関数
        */

        /** 現在のシーンの確認関数*/
        void CheckNowScene();

        /** 入力確認関数*/
        void InputCheck();
    };

}/** namespace My3dApp*/