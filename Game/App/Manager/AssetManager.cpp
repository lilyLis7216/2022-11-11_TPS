#include "AssetManager.h"
#include "DxLib.h"

namespace My3dApp
{
    /** アセットマネージャインスタンスへのポインタ定義*/
    AssetManager* AssetManager::instance = nullptr;

    /**
    * コンストラクタ
    */
    AssetManager::AssetManager()
    {
        instance = nullptr;
    }

    /**
    * デストラクタ
    */
    AssetManager::~AssetManager()
    {
    }

    /**
    * インスタンスの生成
    */
    void AssetManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new AssetManager();
        }
    }

    /**
    * インスタンスの削除
    */
    void AssetManager::DeleteInstance()
    {
        ReleaseAll();
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void AssetManager::AddSoundEffect(string fileName, string key)
    {
        /** keyとサウンドを記録する*/
        instance->soundEffectMap.emplace(key, LoadSoundMem(fileName.c_str()));
    }

    void AssetManager::PlaySoundEffect(string key)
    {
        /** keyを用いたサウンドの特定*/
        auto sound = instance->soundEffectMap[key];

        /** 再生されていなければ*/
        if (!CheckSoundMem(sound))
        {
            /** 再生する*/
            PlaySoundMem(sound, DX_PLAYTYPE_BACK);
        }
    }

    void AssetManager::StopSoundEffect(string key)
    {
        /** keyを用いたサウンドの特定*/
        auto sound = instance->soundEffectMap[key];

        /** 再生されていれば*/
        if (CheckSoundMem(sound))
        {
            /** 停止する*/
            StopSoundMem(sound);
        }
    }

    void AssetManager::StopAllSE()
    {
        /**
        * 後で修正する
        * 一旦ゴリ押し
        */
        //StopSoundEffect("title");
    }

    /**
    * @brief メッシュの取得
    * 
    * @param[in] fileName 取得したいメッシュのファイル名
    * @return int メッシュのハンドル
    */
    int AssetManager::ProcureMesh(string fileName)
    {
        int meshID = 0;

        /** 以前に登録されていないかを調べる*/
        auto itr = instance->meshMap.find(fileName);

        /** 見つからなかった場合*/
        if (itr == instance->meshMap.end())
        {
            /** 新しく読み込み*/
            meshID = MV1LoadModel(fileName.c_str());

            if (meshID == -1)
            {
                return meshID;
            }

            /** fileNameとmeshIDを記録する*/
            instance->meshMap.emplace(fileName, meshID);
        }

        /** 複製したものをmeshIDに入れる*/
        meshID = MV1DuplicateModel(instance->meshMap[fileName]);

        /**
        * メッシュを使うキャラが複数いた場合に、原本を消されると困るため
        * メッシュのコピー削除用にduplicateMeshに保存
        */
        instance->duplicateMesh.push_back(meshID);

        return meshID;
    }

    void AssetManager::ReleaseMesh(int meshID)
    {
        /** meshIDを探して*/
        auto itr = find(instance->duplicateMesh.begin(), instance->duplicateMesh.end(), meshID);

        if (itr == instance->duplicateMesh.end())
        {
            return;
        }

        /** メッシュの解放*/
        MV1DeleteModel(meshID);

        /** 末尾のデータと入れ替えて末尾を削除*/
        iter_swap(itr, instance->duplicateMesh.end() - 1);
        instance->duplicateMesh.pop_back();
    }

    int AssetManager::ProcureAnimation(string fileName)
    {
        int animID = 0;

        /** 見つからなかった場合*/
        auto itr = instance->animationMap.find(fileName);

        if (itr == instance->animationMap.end())
        {
            /** 新しく読み込み*/
            animID = MV1LoadModel(fileName.c_str());

            if (animID == -1)
            {
                return animID;
            }

            /** fileNameとanimIDを記録する*/
            instance->animationMap.emplace(fileName, animID);
        }

        return instance->animationMap[fileName];
    }

    void AssetManager::ReleaseAll()
    {
        /** 全ての複製を削除*/
        for (auto itr = instance->duplicateMesh.begin(); itr != instance->duplicateMesh.end(); ++itr)
        {
            MV1DeleteModel(*itr);
        }
        instance->duplicateMesh.clear();

        /** 全てのアニメーションを解放*/
        for (auto itr = instance->animationMap.begin(); itr != instance->animationMap.end(); ++itr)
        {
            MV1DeleteModel(itr->second);
        }
        instance->animationMap.clear();

        /** 全てのモデルを解放*/
        for (auto itr = instance->meshMap.begin(); itr != instance->meshMap.end(); ++itr)
        {
            MV1DeleteModel(itr->second);
        }
        instance->meshMap.clear();

        /** 全てのSEを削除*/
        for (auto itr = instance->soundEffectMap.begin(); itr != instance->soundEffectMap.end(); ++itr)
        {
            DeleteSoundMem(itr->second);
        }
        instance->soundEffectMap.clear();

    }

}/** namespace My3dApp*/