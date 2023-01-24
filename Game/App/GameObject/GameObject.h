#pragma once

#include "DxLib.h"
#include "ObjectTag.h"
#include "../Library/CollisionType.h"
#include "../Library/Collision.h"

namespace My3dApp
{
    /// <summary>
    /// �Q�[���I�u�W�F�N�g�i���N���X�j
    /// </summary>
    class GameObject
    {
    protected:
        // �^�O�i�I�u�W�F�N�g�̎�ށj
        ObjectTag tag;

        // ���f��
        int modelHandle;

        // �I�u�W�F�N�g�̍��W
        VECTOR pos;

        // �����
        bool isVisible;

        // �������
        bool isAlive;

        // �n��ɂ��邩�ǂ���
        bool onGround;

        // �����蔻��̎��
        CollisionType collisionType;

        // ���������蔻��
        LineSegment collisionLine;

        // ���̓����蔻��
        Sphere collisionSphere;

        // �J�v�Z�������蔻��
        Capsule collisionCapsule;

        // ���f�������蔻��
        int collisionModel;

        // �����蔻��̕`��
        void DrawCollider();

        // �����蔻��ʒu�̍X�V
        void CollisionUpdate();

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̃^�O</param>
        GameObject(ObjectTag tag);

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="tag">�I�u�W�F�N�g�̃^�O</param>
        /// <param name="pos">�����ʒu</param>
        GameObject(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// ���z�f�X�g���N�^
        /// </summary>
        virtual ~GameObject();

        /// <summary>
        /// �Q�[���I�u�W�F�N�g�̍X�V�i�������z�֐��j
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        virtual void Update(float deltaTime) = 0;

        /// <summary>
        /// �Q�[���I�u�W�F�N�g�̕`��i���z�֐��j
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// �I�u�W�F�N�g�̃^�O�̎擾
        /// </summary>
        /// <returns>�I�u�W�F�N�g�������Ă���^�O</returns>
        ObjectTag GetTag() const { return tag; }

        /// <summary>
        /// �ʒu�̎擾
        /// </summary>
        /// <returns>�I�u�W�F�N�g�̌��݈ʒu</returns>
        const VECTOR& GetPos() const { return pos; }

        /// <summary>
        /// �ʒu�̕ύX
        /// </summary>
        /// <param name="set">�ύX�������ʒu</param>
        void SetPos(const VECTOR set) { pos = set; }

        /// <summary>
        /// ����Ԃ̎擾
        /// </summary>
        /// <returns>���Ȃ�true �s���Ȃ�false</returns>
        bool GetVisible() const { return isVisible; }

        /// <summary>
        /// ����Ԃ̕ύX
        /// </summary>
        /// <param name="set">�ύX���������</param>
        void SetVisible(bool set) { isVisible = set; }

        /// <summary>
        /// ������Ԃ̎擾
        /// </summary>
        /// <returns>�����Ă�����true ����ł�����false</returns>
        bool GetAlive() const { return isAlive; }

        /// <summary>
        /// ������Ԃ̕ύX
        /// </summary>
        /// <param name="set">�ύX���������</param>
        void SetAlive(bool set) { isAlive = set; }

        /// <summary>
        /// ���̃I�u�W�F�N�g�ƏՓ˂����Ƃ��̃��A�N�V����
        /// </summary>
        /// <param name="other">�����Ƃ͈قȂ�I�u�W�F�N�g</param>
        virtual void OnCollisionEnter(const GameObject* other) {};

        /// <summary>
        /// ���̃I�u�W�F�N�g�Ƃ̓����蔻��
        /// </summary>
        /// <param name="other">�����蔻��𒲂ׂ����I�u�W�F�N�g</param>
        virtual void Collision(GameObject* other) {};

        /// <summary>
        /// �����蔻���ނ̎擾
        /// </summary>
        /// <returns>�I�u�W�F�N�g�������Ă��铖���蔻����</returns>
        CollisionType GetCollisionType() const { return collisionType; }

        /// <summary>
        /// ���������蔻��̎擾
        /// </summary>
        /// <returns>�����̓����蔻��</returns>
        LineSegment GetCollisionLine() const { return collisionLine; }

        /// <summary>
        /// ���̓����蔻��̎擾
        /// </summary>
        /// <returns>���̂̓����蔻��</returns>
        Sphere GetCollisionSphere() const { return collisionSphere; }

        /// <summary>
        /// �J�v�Z�������蔻��̎擾
        /// </summary>
        /// <returns>�J�v�Z���̓����蔻��</returns>
        Capsule GetCollisionCapsule() const { return collisionCapsule; }

        /// <summary>
        /// ���f�������蔻��̎擾
        /// </summary>
        /// <returns>���f���̓����蔻��</returns>
        int GetCollisionModel() const { return collisionModel; }

    };
}// namespace My3dApp