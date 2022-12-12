#pragma once

#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../GameObject/ObjectTag.h"

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// �Q�[���I�u�W�F�N�g�}�l�[�W��
    /// </summary>
    class GameObjectManager final
    {
    private:
        /** �R���X�g���N�^�i�V���O���g���j*/

        /// <summary>
        /// �R���X�g���N�^�i�V���O���g���j
        /// </summary>
        GameObjectManager();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~GameObjectManager();

        // �Q�[���I�u�W�F�N�g�}�l�[�W���̗B��̃C���X�^���X
        static GameObjectManager* instance;

        // �ۗ��I�u�W�F�N�g
        vector<GameObject*> pendingObjects;

        // ���s�I�u�W�F�N�g
        unordered_map<ObjectTag, vector<GameObject*>> objects;

    public:
        /// <summary>
        /// �C���X�^���X�̐���
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// �C���X�^���X�̍폜
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// �Q�[���I�u�W�F�N�g�}�l�[�W���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        static void Update(float deltaTime);

        /// <summary>
        /// �Q�[���I�u�W�F�N�g�}�l�[�W���̕`��
        /// </summary>
        static void Draw();

        /// <summary>
        /// �I�u�W�F�N�g�̓o�^
        /// </summary>
        /// <param name="newObject">�o�^����I�u�W�F�N�g</param>
        static void Entry(GameObject* newObject);

        /// <summary>
        /// �I�u�W�F�N�g�̍폜
        /// </summary>
        /// <param name="releaseObject">�폜����I�u�W�F�N�g
        /// </param>
        static void Release(GameObject* releaseObject);

        /// <summary>
        /// �S�I�u�W�F�N�g�폜
        /// </summary>
        static void ReleaseAllObject();

        /// <summary>
        /// �����蔻��
        /// </summary>
        static void Collision();

        /// <summary>
        /// �I�u�W�F�N�g�^�O��̍ŏ���GameObject��Ԃ�
        /// </summary>
        /// <param name="tag"></param>
        /// <returns></returns>
        static GameObject* GetFirstGameObject(ObjectTag tag);
    };
}// namespace My3dApp