#include "AssetManager.h"
#include "DxLib.h"

namespace My3dApp
{
    // �A�Z�b�g�}�l�[�W���C���X�^���X�ւ̃|�C���^��`
    AssetManager* AssetManager::instance = nullptr;

    AssetManager::AssetManager()
    {
        instance = nullptr;
    }

    AssetManager::~AssetManager()
    {
    }

    void AssetManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new AssetManager();
        }
    }

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
        // �L�[�ƃT�E���h���L�^����
        instance->soundEffectMap.emplace(key, LoadSoundMem(fileName.c_str()));
    }

    void AssetManager::PlaySoundEffect(string key)
    {
        // �L�[��p�����T�E���h�̌���
        auto sound = instance->soundEffectMap[key];

        // �Đ�����Ă��Ȃ����
        if (!CheckSoundMem(sound))
        {
            // �Đ�����
            PlaySoundMem(sound, DX_PLAYTYPE_BACK);
        }
    }

    void AssetManager::StopSoundEffect(string key)
    {
        // �L�[��p�����T�E���h�̌���
        auto sound = instance->soundEffectMap[key];

        // �Đ�����Ă���� 
        if (CheckSoundMem(sound))
        {
            // ��~����
            StopSoundMem(sound);
        }
    }

    void AssetManager::StopAllSE()
    {
       
        //! �̂��ɏC��
        //StopSoundEffect("title");
    }

    int AssetManager::GetMesh(string fileName)
    {
        int meshID = 0;

        // �ȑO�ɓo�^����Ă��Ȃ����𒲂ׂ�
        auto itr = instance->meshMap.find(fileName);

        // ������Ȃ������ꍇ
        if (itr == instance->meshMap.end())
        {
            // �V�����ǂݍ���
            meshID = MV1LoadModel(fileName.c_str());

            if (meshID == -1)
            {
                return meshID;
            }

            // fileName��meshID���L�^����
            instance->meshMap.emplace(fileName, meshID);
        }

        // �����������̂�meshID�ɓ����
        meshID = MV1DuplicateModel(instance->meshMap[fileName]);

        // ���b�V�����g���L���������������ꍇ�ɁA���{���������ƍ��邽��
        // ���b�V���̃R�s�[�폜�p��duplicateMesh�ɕۑ�
        instance->duplicateMesh.push_back(meshID);

        return meshID;
    }

    void AssetManager::ReleaseMesh(int meshID)
    {
        // meshID��T����
        auto itr = find(instance->duplicateMesh.begin(), instance->duplicateMesh.end(), meshID);

        if (itr == instance->duplicateMesh.end())
        {
            return;
        }

        // ���b�V���̉��
        MV1DeleteModel(meshID);

        // �����̃f�[�^�Ɠ���ւ��Ė������폜
        iter_swap(itr, instance->duplicateMesh.end() - 1);
        instance->duplicateMesh.pop_back();
    }

    int AssetManager::GetAnimation(string fileName)
    {
        int animID = 0;

        auto itr = instance->animationMap.find(fileName);

        // ������Ȃ������ꍇ
        if (itr == instance->animationMap.end())
        {
            // �V�����ǂ݂���
            animID = MV1LoadModel(fileName.c_str());

            if (animID == -1)
            {
                return animID;
            }

            // fileName��animID���L�^����
            instance->animationMap.emplace(fileName, animID);
        }

        return instance->animationMap[fileName];
    }

    void AssetManager::ReleaseAll()
    {
        // ���ׂĂ̕������폜
        for (auto itr = instance->duplicateMesh.begin(); itr != instance->duplicateMesh.end(); ++itr)
        {
            MV1DeleteModel(*itr);
        }
        instance->duplicateMesh.clear();

        // ���ׂẴA�j���[�V���������
        for (auto itr = instance->animationMap.begin(); itr != instance->animationMap.end(); ++itr)
        {
            MV1DeleteModel(itr->second);
        }
        instance->animationMap.clear();

        // ���ׂẴ��f�������
        for (auto itr = instance->meshMap.begin(); itr != instance->meshMap.end(); ++itr)
        {
            MV1DeleteModel(itr->second);
        }
        instance->meshMap.clear();

        // ���ׂẴT�E���h�����
        for (auto itr = instance->soundEffectMap.begin(); itr != instance->soundEffectMap.end(); ++itr)
        {
            DeleteSoundMem(itr->second);
        }
        instance->soundEffectMap.clear();
    }
}// namesapce My3dApp