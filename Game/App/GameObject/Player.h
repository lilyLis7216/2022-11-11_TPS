#pragma once

#include "GameObject.h"
#include <DxLib.h>

namespace My3dApp
{
    class Player : public GameObject
    {
    private:
        /** ����*/
        VECTOR dir;

        /** �ڕW����*/
        VECTOR aimDir;

        /** ���x*/
        VECTOR speed;

        /** �A�j���[�V�����̎��ID*/
        int animTypeID;

        /** ��]����*/
        bool isRotate;

        /** �p�b�h�̓��͏��*/
        int padInputState;

        /** �X�e�B�b�N��x���W*/
        int stickX;

        /** �X�e�B�b�N��y���W*/
        int stickY;

        /** ���͊m�F*/
        void InputCheck();

        /** �ړ�*/
        void Move(float deltaTime);

    public:
        /** �R���X�g���N�^*/
        Player();

        /** �f�X�g���N�^*/
        ~Player();

        /** �v���C���[�̍X�V*/
        void Update(float deltaTime) override;

        /** �v���C���[�̕`��*/
        void Draw() override;
    };

}/** namespace My3dApp*/