#pragma once

#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../GameObject/ObjectTag.h"

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// ゲームオブジェクトマネージャ
    /// </summary>
    class GameObjectManager final
    {
    private:
        /** コンストラクタ（シングルトン）*/

        /// <summary>
        /// コンストラクタ（シングルトン）
        /// </summary>
        GameObjectManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~GameObjectManager();

        // ゲームオブジェクトマネージャの唯一のインスタンス
        static GameObjectManager* instance;

        // 保留オブジェクト
        vector<GameObject*> pendingObjects;

        // 実行オブジェクト
        unordered_map<ObjectTag, vector<GameObject*>> objects;

    public:
        /// <summary>
        /// インスタンスの生成
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// インスタンスの削除
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// ゲームオブジェクトマネージャの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        static void Update(float deltaTime);

        /// <summary>
        /// ゲームオブジェクトマネージャの描画
        /// </summary>
        static void Draw();

        /// <summary>
        /// オブジェクトの登録
        /// </summary>
        /// <param name="newObject">登録するオブジェクト</param>
        static void Entry(GameObject* newObject);

        /// <summary>
        /// オブジェクトの削除
        /// </summary>
        /// <param name="releaseObject">削除するオブジェクト
        /// </param>
        static void Release(GameObject* releaseObject);

        /// <summary>
        /// 全オブジェクト削除
        /// </summary>
        static void ReleaseAllObject();

        /// <summary>
        /// 当たり判定
        /// </summary>
        static void Collision();

        /// <summary>
        /// オブジェクトタグ種の最初のGameObjectを返す
        /// </summary>
        /// <param name="tag"></param>
        /// <returns></returns>
        static GameObject* GetFirstGameObject(ObjectTag tag);
    };
}// namespace My3dApp