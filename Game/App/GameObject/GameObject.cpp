#include "GameObject.h"

namespace My3dApp
{
    /** �R���X�g���N�^�i�^�O�̂݁j
    *
    * @param[in] tag �I�u�W�F�N�g�̃^�O
    */
    GameObject::GameObject(ObjectTag tag)
        : GameObject(tag, initPos)
    {
    }

    /** �R���X�g���N�^�i�^�O�A�ʒu�w��j
    *
    * @param[in] tag �I�u�W�F�N�g�̃^�O
    * @param[in] pos �I�u�W�F�N�g�̈ʒu
    */
    GameObject::GameObject(ObjectTag tag, VECTOR pos)
        : tag(tag)
        , modelHandle(-1)
        , visible(true)
        , alive(true)
        , collisionType()
        , collisionLine()
        , collisionSphere()
        , collisionCapsule()
        , collisionModel()
    {
        this->pos = pos;
    }

    /**
    * ���z�f�X�g���N�^
    */
    GameObject::~GameObject()
    {
        /** ���f���̌�n��*/
        if (modelHandle == -1)
        {
            modelHandle = -1;
        }
    }

    /**
    * �`��
    */
    void GameObject::Draw()
    {
        /** �����Ȃ�*/
    }

    void GameObject::DrawCollider()
    {
        /** ���������蔻��̕`��*/
        DrawLine3D(collisionLine.worldStart, collisionLine.worldEnd, GetColor(255, 255, 0));

        /** ���̓����蔻��̕`��*/
        DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);

        /** �J�v�Z�������蔻��̕`��*/
        DrawCapsule3D(collisionCapsule.worldStart, collisionCapsule.worldEnd, collisionCapsule.radius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);

        /** �����蔻�胂�f�������݂���ꍇ�͔������`��*/
        if (collisionModel != -1)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(collisionModel);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }

    void GameObject::CollisionUpdate()
    {
        collisionSphere.Move(pos);

        collisionLine.Move(pos);

        collisionCapsule.Move(pos);

        /** ���f���̓����蔻������č\�z*/
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);

            MV1SetupCollInfo(collisionModel);
        }
    }
}/** namespace My3dApp*/