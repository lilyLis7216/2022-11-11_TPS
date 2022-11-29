#pragma once
#include <DxLib.h>
#include "ObjectTag.h"

namespace My3dApp
{
    class GameObject
    {
    protected:
        /** タグ（オブジェクトの種類）*/
        ObjectTag tag;

        /** モデル*/
        int modelHandle;

        /** 座標*/
        VECTOR pos;

        /** 座標の初期値*/
        VECTOR initPos = VGet(0, 0, 0);

    public:
        /** コンストラクタ（タグのみ）
        * 
        * @param[in] tag オブジェクトのタグ
        */
        GameObject(ObjectTag tag);

        /** コンストラクタ（タグ、位置指定）
        * 
        * @param[in] tag オブジェクトのタグ
        * @param[in] pos オブジェクトの位置
        */
        GameObject(ObjectTag tag, VECTOR pos);

        /** 仮想デストラクタ*/
        virtual ~GameObject();

        /**
        * 更新処理（純粋仮想関数）
        * 
        * @param[in] deltaTime 1フレームの経過時間
        */
        virtual void Update(float deltaTime) = 0;

        /** 描画処理（仮想関数）*/
        virtual void Draw();
    };

}/** namespace My3dApp*/