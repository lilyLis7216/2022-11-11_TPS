#pragma once
#include <DxLib.h>
#include "ObjectTag.h"

namespace My3dApp
{
    class GameObject
    {
    protected:
        /** �^�O�i�I�u�W�F�N�g�̎�ށj*/
        ObjectTag tag;

        /** ���f��*/
        int modelHandle;

        /** ���W*/
        VECTOR pos;

        /** ���W�̏����l*/
        VECTOR initPos = VGet(0, 0, 0);

    public:
        /** �R���X�g���N�^�i�^�O�̂݁j
        * 
        * @param[in] tag �I�u�W�F�N�g�̃^�O
        */
        GameObject(ObjectTag tag);

        /** �R���X�g���N�^�i�^�O�A�ʒu�w��j
        * 
        * @param[in] tag �I�u�W�F�N�g�̃^�O
        * @param[in] pos �I�u�W�F�N�g�̈ʒu
        */
        GameObject(ObjectTag tag, VECTOR pos);

        /** ���z�f�X�g���N�^*/
        virtual ~GameObject();

        /**
        * �X�V�����i�������z�֐��j
        * 
        * @param[in] deltaTime 1�t���[���̌o�ߎ���
        */
        virtual void Update(float deltaTime) = 0;

        /** �`�揈���i���z�֐��j*/
        virtual void Draw();
    };

}/** namespace My3dApp*/