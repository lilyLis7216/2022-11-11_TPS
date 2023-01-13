#include "GameObjectManager.h"

namespace My3dApp
{
    // �Q�[���I�u�W�F�N�g�}�l�[�W���C���X�^���X�ւ̃|�C���^��`
    GameObjectManager* GameObjectManager::instance = nullptr;

    GameObjectManager::GameObjectManager()
        : pendingObjects()
        , objects()
    {
        instance = nullptr;
    }

    GameObjectManager::~GameObjectManager()
    {
        ReleaseAllObject();
    }

    void GameObjectManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new GameObjectManager();
        }
    }

    void GameObjectManager::DeleteInstance()
    {
        ReleaseAllObject();

        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void GameObjectManager::Update(float deltaTime)
    {

        for (auto& tag : ObjectTagAll)
        {
            // �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g�̍X�V
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                instance->objects[tag][i]->Update(deltaTime);
            }
        }

        for (auto pending : instance->pendingObjects)
        {
            ObjectTag tag = pending->GetTag();
            instance->objects[tag].emplace_back(pending);
        }

        instance->pendingObjects.clear();

        vector<GameObject*> deadObjects;
        for (auto& tag : ObjectTagAll)
        {
            for (auto obj : instance->objects[tag])
            {
                if (!obj->GetAlive())
                {
                    deadObjects.emplace_back(obj);
                }
            }

            instance->objects[tag].erase(remove_if(begin(instance->objects[tag]), end(instance->objects[tag]), 
                [](GameObject* g) {return !g->GetAlive(); }), cend(instance->objects[tag]));
        }

        // ����ł���GameObject��������delete
        while (!deadObjects.empty())
        {
            delete deadObjects.back();
            deadObjects.pop_back();
        }
    }

    void GameObjectManager::Draw()
    {
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                if (instance->objects[tag][i]->GetVisible())
                {
                    instance->objects[tag][i]->Draw();
                }
            }
        }
    }

    void GameObjectManager::Entry(GameObject* newObject)
    {
        // �ۗ��I�u�W�F�N�g�Ɉꎞ�ۑ�
        instance->pendingObjects.push_back(newObject);
    }

    void GameObjectManager::Release(GameObject* releaseObject)
    {
        auto pending = instance->pendingObjects;
        auto itr = find(pending.begin(), pending.end(), releaseObject);
        if (itr != pending.end())
        {
            iter_swap(itr, pending.end() - 1);
            pending.pop_back();

            return;
        }

        auto object = instance->objects[releaseObject->GetTag()];
        itr = find(object.begin(), object.end(), releaseObject);
        if (itr != object.end())
        {
            iter_swap(itr, object.end() - 1);
            delete object.back();
        }
    }

    void GameObjectManager::ReleaseAllObject()
    {
        while (!instance->pendingObjects.empty())
        {
            delete instance->pendingObjects.back();
        }

        for (auto& tag : ObjectTagAll)
        {
            while (!instance->objects[tag].empty())
            {
                delete instance->objects[tag].back();
                instance->objects[tag].pop_back();
            }
        }
    }

    void GameObjectManager::Collision()
    {
        // �v���C���[�̓����蔻��
        for (int playerNum = 0; playerNum < instance->objects[ObjectTag::Player].size(); ++playerNum)
        {
            // �}�b�v�Ƃ̓����蔻��
            for (int mapNum = 0; mapNum < instance->objects[ObjectTag::Map].size(); ++mapNum)
            {
                instance->objects[ObjectTag::Player][playerNum]->OnCollisionEnter(instance->objects[ObjectTag::Map][mapNum]);
            }

            // �G�l�~�[�Ƃ̓����蔻��
            for (int enemyNum = 0; enemyNum < instance->objects[ObjectTag::Enemy].size(); ++enemyNum)
            {
                instance->objects[ObjectTag::Player][playerNum]->OnCollisionEnter(instance->objects[ObjectTag::Enemy][enemyNum]);
            }
        }

        // �G�l�~�[�̓����蔻��
        for (int enemyNum = 0; enemyNum < instance->objects[ObjectTag::Enemy].size(); ++enemyNum)
        {
            // �}�b�v�Ƃ̓����蔻��
            for (int mapNum = 0; mapNum < instance->objects[ObjectTag::Map].size(); ++mapNum)
            {
                instance->objects[ObjectTag::Enemy][enemyNum]->OnCollisionEnter(instance->objects[ObjectTag::Map][mapNum]);
            }

            // ���g�������G�l�~�[�Ƃ̓����蔻��
            for (int anotherEnemyNum = 0; anotherEnemyNum < instance->objects[ObjectTag::Enemy].size(); ++anotherEnemyNum)
            {
                if (enemyNum != anotherEnemyNum)
                {
                    instance->objects[ObjectTag::Enemy][enemyNum]->OnCollisionEnter(instance->objects[ObjectTag::Enemy][anotherEnemyNum]);
                }
            }
        }
    }

    GameObject* GameObjectManager::GetFirstGameObject(ObjectTag tag)
    {
        if (instance->objects[tag].size() == 0)
        {
            return nullptr;
        }
        return instance->objects[tag][0];
    }
}// namespace My3dApp