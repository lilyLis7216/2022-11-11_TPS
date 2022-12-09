#pragma once

#include "GameObject.h"

namespace My3dApp
{
    class Map : public GameObject
    {
    public:
        /** �R���X�g���N�^*/
        Map();

        /** �R���X�g���N�^�i���W�w��j*/
        Map(VECTOR pos);

        /** �f�X�g���N�^*/
        ~Map();

        /** ���f���̓ǂݍ���*/
        void ModelLoad();

        /** �X�V*/
        void Update(float deltaTime) override;

        /** �`��*/
        void Draw() override;
    };
}/** namespace My3dApp*/