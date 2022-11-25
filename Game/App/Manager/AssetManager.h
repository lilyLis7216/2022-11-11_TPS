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

        /** ���b�V���̌��{*/
        unordered_map<string, int>originalMeshMap;

        /** �A�j���[�V�����̌��{*/
        unordered_map<string, int>originalAnimationMap;

        /** �����������b�V��*/
        vector<int> duplicateMesh;

    public:
        /** �C���X�^���X�̐���*/
        static void CreateInstance();

        /** �C���X�^���X�̍폜*/
        static void DeleteInstance();

        static void ProcureMesh();

        static void ReleaseMesh();

        static void ReleaseAll();
    };
}/** namespace My3dApp*/