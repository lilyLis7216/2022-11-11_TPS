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
        /** �R���X�g���N�^�i�V���O���g���j*/
        GameObjectManager();

        /** �f�X�g���N�^*/
        ~GameObjectManager();

        /** �}�l�[�W���̃C���X�^���X*/
        static GameObjectManager* instance;

        /** �ۗ��I�u�W�F�N�g*/
        vector<GameObject*> pendingObjects;

        /** ���s�I�u�W�F�N�g*/
        unordered_map<ObjectTag, vector<GameObject*>> objects;

    public:
        /** �C���X�^���X�̐���*/
        static void CreateInstance();

        /** �C���X�^���X�̍폜*/
        static void DeleteInstance();

        /** �X�V*/
        static void Update(float deltaTime);

        /** �`��*/
        static void Draw();

        /** �I�u�W�F�N�g�̓o�^*/
        static void Entry(GameObject* newObject);

        /** �I�u�W�F�N�g�̍폜*/
        static void Release(GameObject* releaseObject);

        /** �S�I�u�W�F�N�g�폜*/
        static void ReleaseAllObject();

        /** �����蔻��*/
        static void Collision();

        /** �I�u�W�F�N�g�^�O��̍ŏ���GameObject��Ԃ�*/
        static GameObject* GetFirstGameObject(ObjectTag tag);
    };
}/** namespace My3dApp*/