#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../Library/AnimationController.h"
#include "../Manager/GameObjectManager.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , animCtrl(nullptr)
        , animTypeID(0)
        , isRotate(false)
    {

        // 3D���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../Assets/Model/test/player.mv1");

        // ���f���̑傫���ݒ�
        MV1SetScale(modelHandle, VGet(1, 1, 1));

        //// �A�j���[�V�����R���g���[���̐���
        //animCtrl = new AnimationController(modelHandle);

        //// �ҋ@�A�j���[�V�����̓ǂݍ���
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimIdle.mv1");

        //// ���s�A�j���[�V�����̓ǂݍ���
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimRun.mv1");

        //// �U���A�j���[�V�����̓ǂݍ���
        //animCtrl->AddAnimation("../Assets/Model/Player/unityChanAnimPunch.mv1");

        //// �����Đ��A�j���[�V�����̏�����
        //animCtrl->StartAnimation(animTypeID);

        // ���W�̏�����
        pos = VGet(0, 0, 0);

        // �����̏�����
        dir = VGet(1, 0, 0);

        aimDir = dir;

        // ���x�̏�����
        speed = VGet(0, 0, 0);

        // �����蔻���ނ����̂ɐݒ�
        collisionType = CollisionType::Sphere;

        // ���[�J���Z���^�[��50
        collisionSphere.localCenter = VGet(0, 50.0f, 0);

        // ���a��30
        collisionSphere.radius = 30.0f;

        // ���������蔻���ݒ�
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));
    }

    Player::~Player()
    {
        // ���f���̃A�����[�h
        AssetManager::ReleaseMesh(modelHandle);

        // �A�j���[�V�����R���g���[���̍폜
        delete animCtrl;
    }

    void Player::Update(float deltaTime)
    {
        //animCtrl->AddAnimationTime(deltaTime);

        RotateCheck();

        Move(deltaTime);

        CollisionUpdate();
    }

    void Player::Draw()
    {
        // 3D���f���̕`��
        MV1DrawModel(modelHandle);

        DrawCollider();
    }

    void Player::OnCollisionEnter(const GameObject* other)
    {
        // ���ׂ�I�u�W�F�N�g�̃^�O���擾
        ObjectTag tag = other->GetTag();

        // �}�b�v�Ƃ̏Փ�
        if (tag == ObjectTag::Map)
        {
            int collModel = other->GetCollisionModel();

            // �}�b�v�Ǝ��g�̋��E���Ƃ̓����蔻��
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

        // �G�Ƃ̏Փ�
        if (tag == ObjectTag::Enemy)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                printfDx("Hit!");
            }
        }
    }

    void Player::Move(float deltaTime)
    {
        // �J�����������Ă���
        GameObject* camera = GameObjectManager::GetFirstGameObject(ObjectTag::Camera);

        // �J�����̐��ʕ����̈ʒu�x�N�g�����v�Z
        VECTOR front = pos - camera->GetPos();

        front.y = 0.0f;

        // �x�N�g���̐��K��
        front = VNorm(front);

        // Y���x�N�g��
        VECTOR YAxis = { 0,1,0 };

        // �����
        VECTOR UP = front;

        // ������
        VECTOR DOWN = VScale(front, -1.0f);

        // �E����
        VECTOR RIGHT = VCross(YAxis, front);

        // ������
        VECTOR LEFT = VScale(RIGHT, -1.0f);

        // �ړ��p�x�N�g��
        VECTOR inputVec = VGet(0, 0, 0);

        // ���͂����������ǂ���
        bool input = false;

        if (GamePad::GetInput(Button::UP) || 0 < GamePad::GetLeftStickY())
        {
            inputVec += UP;
            input = true;
        }

        if (GamePad::GetInput(Button::DOWN) || GamePad::GetLeftStickY() < 0)
        {
            inputVec += DOWN;
            input = true;
        }

        if (GamePad::GetInput(Button::LEFT) || GamePad::GetLeftStickX() < 0)
        {
            inputVec += LEFT;
            input = true;
        }

        if (GamePad::GetInput(Button::RIGHT) || 0 < GamePad::GetLeftStickX())
        {
            inputVec += RIGHT;
            input = true;
        }

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

            speed = inputVec + (inputVec * deltaTime * 200.0f);

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

    void Player::RotateCheck()
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