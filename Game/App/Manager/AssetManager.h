#pragma once
#include <string>
#include <unordered_map>

using namespace std;

namespace My3dApp
{
    /**
    * �A�Z�b�g�}�l�[�W���N���X
    */
    class AssetManager final
    {
    private:
        /** �R���X�g���N�^*/
        AssetManager();

        /** �f�X�g���N�^*/
        ~AssetManager();

        /** �C���X�^���X�ւ̃|�C���^*/
        static AssetManager* instance;

        /** ���b�V���̃}�b�v�i���{�j*/
        unordered_map<string, int>meshMap;

        /** �����������b�V��*/
        vector<int> duplicateMesh;

        /** �A�j���[�V�����̃}�b�v*/
        unordered_map<string, int>animationMap;

        /** SE�̃}�b�v*/
        unordered_map<string, int>soundEffectMap;

    public:
        /** �C���X�^���X�̐���*/
        static void CreateInstance();

        /** �C���X�^���X�̍폜*/
        static void DeleteInstance();

        /** SE�̒ǉ�*/
        static void AddSoundEffect(string fileName, string key);

        /** SE�̍Đ�*/
        static void PlaySoundEffect(string key);

        /** SE�̒�~*/
        static void StopSoundEffect(string key);

        /** �S�Ă�SE�̒�~*/
        static void StopAllSE();

        /** ���b�V���̎擾*/
        static int GetMesh(string fileName);

        /** ���b�V���̉��*/
        static void ReleaseMesh(int meshID);

        /** �A�j���[�V�����̎擾*/
        static int GetAnimation(string fileName);

        /** �S�ẴA�Z�b�g�̉��*/
        static void ReleaseAll();
    };
}/** namespace My3dApp*/