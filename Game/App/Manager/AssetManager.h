#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// アセットマネージャ
    /// </summary>
    class AssetManager final
    {
    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        AssetManager();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~AssetManager();

        // アセットマネージャの唯一のインスタンス
        static AssetManager* instance;

        // メッシュのマップ（原本）
        unordered_map<string, int>meshMap;

        // 複製したメッシュ
        vector<int> duplicateMesh;

        // アニメーションのマップ
        unordered_map<string, int>animationMap;

        // SEのマップ
        unordered_map<string, int>soundEffectMap;

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
        /// SEの追加
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="key"></param>
        static void AddSoundEffect(string fileName, string key, int volume);

        /// <summary>
        /// SEの再生
        /// </summary>
        /// <param name="key"></param>
        static void PlaySoundEffect(string key, bool isContinue);

        /// <summary>
        /// SEの停止
        /// </summary>
        /// <param name="key"></param>
        static void StopSoundEffect(string key);

        /// <summary>
        /// すべてのSEの停止
        /// </summary>
        static void StopAllSE();

        /// <summary>
        /// メッシュの取得
        /// </summary>
        /// <param name="fileName">取得したいメッシュのファイル名</param>
        /// <returns>メッシュのハンドル</returns>
        static int GetMesh(string fileName);

        /// <summary>
        /// メッシュの解放
        /// </summary>
        /// <param name="meshID"></param>
        static void ReleaseMesh(int meshID);

        /// <summary>
        /// アニメーションの取得
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static int GetAnimation(string fileName);

        /// <summary>
        /// すべてのアセットの解放
        /// </summary>
        static void ReleaseAll();

    };
}// namespace My3dApp