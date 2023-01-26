#pragma once

namespace My3dApp
{
    class Shadow
    {
    private:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Shadow();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Shadow();

        // �V���h�E�̗B��̃C���X�^���X
        static Shadow* instance;

        // �V���h�E�}�b�v
        static int shadowMap;

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
        /// �V���h�E�}�b�v�̎擾
        /// </summary>
        /// <returns>�V���h�E�}�b�v</returns>
        static int GetShadowMap() { return shadowMap; }
    };
}