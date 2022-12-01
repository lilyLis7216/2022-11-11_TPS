#pragma once
#include <string>
#include <unordered_map>

using namespace std;

namespace My3dApp
{
    /**
    * アセットマネージャクラス
    */
    class AssetManager final
    {
    private:
        /** コンストラクタ*/
        AssetManager();

        /** デストラクタ*/
        ~AssetManager();

        /** インスタンスへのポインタ*/
        static AssetManager* instance;

        /** メッシュのマップ（原本）*/
        unordered_map<string, int>meshMap;

        /** 複製したメッシュ*/
        vector<int> duplicateMesh;

        /** アニメーションのマップ*/
        unordered_map<string, int>animationMap;

        /** SEのマップ*/
        unordered_map<string, int>soundEffectMap;

    public:
        /** インスタンスの生成*/
        static void CreateInstance();

        /** インスタンスの削除*/
        static void DeleteInstance();

        /** SEの追加*/
        static void AddSoundEffect(string fileName, string key);

        /** SEの再生*/
        static void PlaySoundEffect(string key);

        /** SEの停止*/
        static void StopSoundEffect(string key);

        /** 全てのSEの停止*/
        static void StopAllSE();

        /** メッシュの取得*/
        static int GetMesh(string fileName);

        /** メッシュの解放*/
        static void ReleaseMesh(int meshID);

        /** アニメーションの取得*/
        static int GetAnimation(string fileName);

        /** 全てのアセットの解放*/
        static void ReleaseAll();
    };
}/** namespace My3dApp*/