#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// �A�Z�b�g�}�l�[�W��
    /// </summary>
    class AssetManager final
    {
    private:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        AssetManager();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~AssetManager();

        // �A�Z�b�g�}�l�[�W���̗B��̃C���X�^���X
        static AssetManager* instance;

        // ���b�V���̃}�b�v�i���{�j
        unordered_map<string, int>meshMap;

        // �����������b�V��
        vector<int> duplicateMesh;

        // �A�j���[�V�����̃}�b�v
        unordered_map<string, int>animationMap;

        // SE�̃}�b�v
        unordered_map<string, int>soundEffectMap;

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
        /// SE�̒ǉ�
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="key"></param>
        static void AddSoundEffect(string fileName, string key, int volume);

        /// <summary>
        /// SE�̍Đ�
        /// </summary>
        /// <param name="key"></param>
        static void PlaySoundEffect(string key, bool isContinue);

        /// <summary>
        /// SE�̒�~
        /// </summary>
        /// <param name="key"></param>
        static void StopSoundEffect(string key);

        /// <summary>
        /// ���ׂĂ�SE�̒�~
        /// </summary>
        static void StopAllSE();

        /// <summary>
        /// ���b�V���̎擾
        /// </summary>
        /// <param name="fileName">�擾���������b�V���̃t�@�C����</param>
        /// <returns>���b�V���̃n���h��</returns>
        static int GetMesh(string fileName);

        /// <summary>
        /// ���b�V���̉��
        /// </summary>
        /// <param name="meshID"></param>
        static void ReleaseMesh(int meshID);

        /// <summary>
        /// �A�j���[�V�����̎擾
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        static int GetAnimation(string fileName);

        /// <summary>
        /// ���ׂẴA�Z�b�g�̉��
        /// </summary>
        static void ReleaseAll();

    };
}// namespace My3dApp