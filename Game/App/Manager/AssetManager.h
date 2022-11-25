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

        /** メッシュの原本*/
        unordered_map<string, int>originalMeshMap;

        /** アニメーションの原本*/
        unordered_map<string, int>originalAnimationMap;

        /** 複製したメッシュ*/
        vector<int> duplicateMesh;

    public:
        /** インスタンスの生成*/
        static void CreateInstance();

        /** インスタンスの削除*/
        static void DeleteInstance();

        static void ProcureMesh();

        static void ReleaseMesh();

        static void ReleaseAll();
    };
}/** namespace My3dApp*/