#pragma once

#include <DxLib.h>
#include "ObjectTag.h"
#include "../Library/CollisionType.h"
#include "../Library/Collision.h"

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

        /** �����*/
        bool visible;

        /** �������*/
        bool alive;

        /** �����蔻��̎��*/
        CollisionType collisionType;

        /** ���������蔻��*/
        LineSegment collisionLine;

        /** ���̓����蔻��*/
        Sphere collisionSphere;

        /** �J�v�Z�������蔻��*/
        Capsule collisionCapsule;

        /** ���f�������蔻��*/
        int collisionModel;

        /** �����蔻��̕`��*/
        void DrawCollider();

        /** �����蔻��ʒu�̍X�V*/
        void CollisionUpdate();

    public:
        /** �R���X�g���N�^�i�^�O�̂݁j*/
        GameObject(ObjectTag tag);

        /** �R���X�g���N�^�i�^�O�A�ʒu�w��j*/
        GameObject(ObjectTag tag, VECTOR pos);

        /** ���z�f�X�g���N�^*/
        virtual ~GameObject();

        /** �X�V�����i�������z�֐��j*/
        virtual void Update(float deltaTime) = 0;

        /** �`�揈���i���z�֐��j*/
        virtual void Draw();

        /** �I�u�W�F�N�g�^�O�̎擾*/
        ObjectTag GetTag() const { return tag; }

        /** �ʒu�̎擾*/
        const VECTOR& GetPos() const { return pos; }

        /** �ʒu�̎w��*/
        void SetPos(const VECTOR set) { pos = set; }

        /** ����Ԃ̎擾*/
        bool GetVisible() const { return visible; }

        /** ����Ԃ̎w��*/
        void SetVisible(bool visible) { this->visible = visible; }

        /** ������Ԃ̎擾*/
        bool GetAlive() const { return alive; }

        /** ������Ԃ̎w��*/
        void SetAlive(bool alive) { this->alive = alive; }

        /** ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����*/
        virtual void OnCollisionEnter(const GameObject* other) {};

        /** ���̃I�u�W�F�N�g�Ƃ̓����蔻��*/
        virtual void Collision(GameObject* other) {};

        /** �����蔻���ނ̎擾*/
        CollisionType GetCollisionType() const { return collisionType; }

        /** ���������蔻��̎擾*/
        LineSegment GetCollisionLine() const { return collisionLine; }

        /** ���̓����蔻��̎擾*/
        Sphere GetCollisionSphere() const { return collisionSphere; }

        /** �J�v�Z�������蔻��̎擾*/
        Capsule GetCollisionCapsule() const { return collisionCapsule; }

        /** ���f�������蔻��̎擾*/
        int GetCollisionModel() const { return collisionModel; }
    };
}/** namespace My3dApp*/