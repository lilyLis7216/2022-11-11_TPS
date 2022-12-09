#pragma once

#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../GameObject/ObjectTag.h"

using namespace std;

namespace My3dApp
{
    class GameObjectManager final
    {
    private:
        /** コンストラクタ（シングルトン）*/
        GameObjectManager();

        /** デストラクタ*/
        ~GameObjectManager();

        /** マネージャのインスタンス*/
        static GameObjectManager* instance;

        /** 保留オブジェクト*/
        vector<GameObject*> pendingObjects;

        /** 実行オブジェクト*/
        unordered_map<ObjectTag, vector<GameObject*>> objects;

    public:
        /** インスタンスの生成*/
        static void CreateInstance();

        /** インスタンスの削除*/
        static void DeleteInstance();

        /** 更新*/
        static void Update(float deltaTime);

        /** 描画*/
        static void Draw();

        /** オブジェクトの登録*/
        static void Entry(GameObject* newObject);

        /** オブジェクトの削除*/
        static void Release(GameObject* releaseObject);

        /** 全オブジェクト削除*/
        static void ReleaseAllObject();

        /** 当たり判定*/
        static void Collision();

        /** オブジェクトタグ種の最初のGameObjectを返す*/
        static GameObject* GetFirstGameObject(ObjectTag tag);
    };
}/** namespace My3dApp*/