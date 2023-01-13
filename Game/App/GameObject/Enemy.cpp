#include "Enemy.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/AnimationController.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "ObjectTag.h"

namespace My3dApp
{
    Enemy::Enemy()
        : Enemy(initPos)
    {
    }

    Enemy::Enemy(VECTOR pos)
        : GameObject(ObjectTag::Enemy, pos)
        , animCtrl(nullptr)
        , animTypeID(0)
        , isRotate(false)
        , moveCount(10.0f)
        , isMove(false)
        , moveTmp(0)
    {
        modelHandle = AssetManager::GetMesh("../asset/model/test/enemy.mv1");

        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        dir = VGet(1, 0, 0);

        aimDir = dir;

        speed = VGet(0, 0, 0);

        collisionType = CollisionType::Sphere;

        collisionSphere.localCenter = VGet(0, 50.0f, 0);

        collisionSphere.radius = 30.0f;

        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));
    }

    Enemy::~Enemy()
    {
        // ���f���̃A�����[�h
        AssetManager::ReleaseMesh(modelHandle);

        // �A�j���[�V�����R���g���[���̍폜
        delete animCtrl;
    }

    void Enemy::Update(float deltaTime)
    {
        Move(deltaTime);

        RotateCheck();
    }

    void Enemy::Draw()
    {
        // ���f���̕`��
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Enemy::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̃^�O���擾
        ObjectTag tag = other->GetTag();

        // �}�b�v�Ƃ̏Փ�
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // �}�b�v�Ǝ��g�̋��E���s�̓����蔻��
            MV1_COLL_RESULT_POLY_DIM collInfo;

            // �������Ă���ꍇ
            if (CollisionPair(collisionSphere, collModel, collInfo))
            {
                // �����߂���
                VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(collisionSphere, collInfo);

                // �����߂�
                pos += pushBackVec;

                // �����蔻����̉��
                MV1CollResultPolyDimTerminate(collInfo);

                // �����蔻��̍X�V
                CollisionUpdate();
            }

            // �w�i�Ƒ������������蔻��
            MV1_COLL_RESULT_POLY collInfoLine;

            // �������Ă���ꍇ
            if (CollisionPair(collisionLine, collModel, collInfoLine))
            {
                // �������Փ˓_�ɍ��킹��
                pos = collInfoLine.HitPosition;

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }
    }

    void Enemy::Move(float deltaTime)
    {
        // �v���C���[�̎擾
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // �v���C���[�̍��W���玩�g�̍��W�������Č����x�N�g�����v�Z����
        VECTOR tmp = player->GetPos() - pos;

        // �����x�N�g���̖�����
        tmp.y = 0;

        // �ړ��p�x�N�g��
        VECTOR inputVec = VGet(0, 0, 0);

        // ���͂����������ǂ���
        bool input = false;

        if (abs(tmp.x) < 200.0f)
        {
            input = true;
        }

        if (abs(tmp.z) < 200.0f)
        {
            input = true;
        }

        inputVec += tmp;

        // ���͂���������
        if (input)
        {
            // ���E�㉺���������Ȃǂœ��̓x�N�g����0�̂Ƃ�
            if (VSquareSize(inputVec) < 0.5f)
            {
                return;
            }

            // �����𐳋K��
            inputVec = VNorm(inputVec);

            // ���͕����͌��݌����Ă�������ƈقȂ邩
            if (IsNearAngle(inputVec, dir))
            {
                dir = inputVec;
            }
            else
            {
                isRotate = true;
                aimDir = inputVec;
            }

            speed = inputVec + (inputVec * deltaTime * 100.0f);

            // �������̃��[�V�������������瑖�胂�[�V������
            if (animTypeID != 1)
            {
                animTypeID = 1;
                //animCtrl->StartAnimation(animTypeID);
            }
        }
        else
        {
            speed *= 0.9f;

            // �����ق��̃��[�V��������������������[�V������
            if (animTypeID != 0)
            {
                animTypeID = 0;
                //animCtrl->StartAnimation(animTypeID);
            }
        }

        pos += speed;

        // 3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        // �����ɍ��킹�ă��f������]
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // ���f���ɉ�]���Z�b�g����
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // �����蔻�胂�f���̈ʒu�X�V
        CollisionUpdate();
    }

    void Enemy::RotateCheck()
    {
        if (isRotate)
        {
            // ��]���ڕW�p�x�ɏ\���߂���Ή�]�I��
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                isRotate = false;
            }
            else
            {
                // ��]������
                VECTOR interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);

                // ��]���ڕW�p�x�𒴂��Ă��Ȃ���
                VECTOR cross1 = VCross(dir, aimDir);
                VECTOR cross2 = VCross(interPolateDir, aimDir);

                // �ڕW�p�x�𒴂�����I��
                if (cross1.y * cross2.y < 0.0f)
                {
                    interPolateDir = aimDir;
                    isRotate = false;
                }

                // �ڕW�x�N�g����10�x�����߂Â����p�x
                dir = interPolateDir;
            }
        }
    }
}// namespace My3dApp