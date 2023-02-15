#include "GameObjectManager.h"
#include "../Library/Shadow.h"

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
        // �V���h�E�}�b�v�ւ̕`��̏���
        ShadowMap_DrawSetup(Shadow::GetShadowMap());

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

        // �V���h�E�}�b�v�ւ̕`����I��
        ShadowMap_DrawEnd();

        for (auto& tag : ObjectTagAll)
        {
            if (tag != ObjectTag::Map)
            {
                // �`��Ɏg�p����V���h�E�}�b�v��ݒ�
                SetUseShadowMap(0, Shadow::GetShadowMap());
            }
            else
            {
                SetUseShadowMap(1, Shadow::GetShadowMap());
            }
            for (int i = 0; i < instance->objects[tag].size(); ++i)
            {
                if (instance->objects[tag][i]->GetVisible())
                {
                    instance->objects[tag][i]->Draw();
                }
            }
        }

        // �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
        SetUseShadowMap(0, -1);
        SetUseShadowMap(1, -1);

        auto tag = ObjectTag::Enemy;
        for (int i = 0; i < instance->objects[tag].size(); ++i)
        {
            if (instance->objects[tag][i]->GetVisible())
            {
                instance->objects[tag][i]->DamageParView(1);
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
            instance->pendingObjects.pop_back();
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
        // ���C���̃^�O
        ObjectTag mainTag;

        // �y�A�̃^�O
        ObjectTag pairTag;

        // �v���C���[�̓����蔻��
        mainTag = ObjectTag::Player;
        for (int playerNum = 0; playerNum < instance->objects[mainTag].size(); ++playerNum)
        {
            // �}�b�v�Ƃ̓����蔻��
            pairTag = ObjectTag::Map;
            for (int mapNum = 0; mapNum < instance->objects[pairTag].size(); ++mapNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][mapNum]);
            }

            // �G�l�~�[�Ƃ̓����蔻��
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }

            // �G�l�~�[�e�Ƃ̓����蔻��
            pairTag = ObjectTag::EnemyBullet;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // �G�l�~�[�e�Ƃ̓����蔻��
            pairTag = ObjectTag::EnemyBulletS;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // �G�l�~�[�e�Ƃ̓����蔻��
            pairTag = ObjectTag::EnemyBulletM;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }

            // �G�l�~�[�e�Ƃ̓����蔻��
            pairTag = ObjectTag::EnemyBulletL;
            for (int eBulletNum = 0; eBulletNum < instance->objects[pairTag].size(); ++eBulletNum)
            {
                instance->objects[mainTag][playerNum]->OnCollisionEnter(instance->objects[pairTag][eBulletNum]);
            }
        }

        // �v���C���[�e�̓����蔻��
        mainTag = ObjectTag::PlayerBullet;
        for (int pBulletNum = 0; pBulletNum < instance->objects[mainTag].size(); ++pBulletNum)
        {
            // �G�Ƃ̓����蔻��
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][pBulletNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }
        }

        // �v���C���[�e�̓����蔻��
        mainTag = ObjectTag::PlayerBulletCharge;
        for (int pBulletNum = 0; pBulletNum < instance->objects[mainTag].size(); ++pBulletNum)
        {
            // �G�Ƃ̓����蔻��
            pairTag = ObjectTag::Enemy;
            for (int enemyNum = 0; enemyNum < instance->objects[pairTag].size(); ++enemyNum)
            {
                instance->objects[mainTag][pBulletNum]->OnCollisionEnter(instance->objects[pairTag][enemyNum]);
            }
        }

        // �G�l�~�[�̓����蔻��
        mainTag = ObjectTag::Enemy;
        for (int enemyNum = 0; enemyNum < instance->objects[mainTag].size(); ++enemyNum)
        {
            // �}�b�v�Ƃ̓����蔻��
            pairTag = ObjectTag::Map;
            for (int mapNum = 0; mapNum < instance->objects[pairTag].size(); ++mapNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][mapNum]);
            }

            // ���g�������G�l�~�[�Ƃ̓����蔻��
            pairTag = ObjectTag::Enemy;
            for (int anotherEnemyNum = 0; anotherEnemyNum < instance->objects[pairTag].size(); ++anotherEnemyNum)
            {
                if (enemyNum != anotherEnemyNum)
                {
                    instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][anotherEnemyNum]);
                }
            }

            pairTag = ObjectTag::PlayerBullet;
            for (int pBulletNum = 0; pBulletNum < instance->objects[pairTag].size(); ++pBulletNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][pBulletNum]);
            }

            pairTag = ObjectTag::PlayerBulletCharge;
            for (int pBulletNum = 0; pBulletNum < instance->objects[pairTag].size(); ++pBulletNum)
            {
                instance->objects[mainTag][enemyNum]->OnCollisionEnter(instance->objects[pairTag][pBulletNum]);
            }
        }

        // �G�l�~�[�e�̓����蔻��
        mainTag = ObjectTag::EnemyBullet;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // �v���C���[�Ƃ̓����蔻��
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // �G�l�~�[�e�̓����蔻��
        mainTag = ObjectTag::EnemyBulletS;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // �v���C���[�Ƃ̓����蔻��
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // �G�l�~�[�e�̓����蔻��
        mainTag = ObjectTag::EnemyBulletM;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // �v���C���[�Ƃ̓����蔻��
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
            }
        }

        // �G�l�~�[�e�̓����蔻��
        mainTag = ObjectTag::EnemyBulletL;
        for (int eBulletNum = 0; eBulletNum < instance->objects[mainTag].size(); ++eBulletNum)
        {
            // �v���C���[�Ƃ̓����蔻��
            pairTag = ObjectTag::Player;
            for (int playerNum = 0; playerNum < instance->objects[pairTag].size(); ++playerNum)
            {
                instance->objects[mainTag][eBulletNum]->OnCollisionEnter(instance->objects[pairTag][playerNum]);
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