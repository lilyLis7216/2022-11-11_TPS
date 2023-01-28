#include "Player.h"
#include "../Manager/AssetManager.h"
#include "../Manager/GameObjectManager.h"
#include "EffekseerForDXLib.h"
#include "../Library/Calc3D.h"
#include "../Library/GamePad.h"
#include "Bullet/NormalBullet.h"
#include "Bullet/ChargeBullet.h"

namespace My3dApp
{
    Player::Player()
        : GameObject(ObjectTag::Player)
        , isRotate(false)
        , shotInterval(0)
        , isCharge(false)
    {
        // 3D���f���̓ǂݍ���
        modelHandle = AssetManager::GetMesh("../asset/model/player.mv1");

        // ���W�̏�����
        pos = VGet(0, 100, 0);

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, pos);

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

        // �����̏�����
        dir = VGet(1, 0, 0);

        // �ڕW�����̏�����
        aimDir = dir;

        // ���x�̏�����
        speed = VGet(0, 0, 0);

        // �����蔻���ނ����̂ɐݒ�
        collisionType = CollisionType::Sphere;

        // �����蔻�苅�̃��[�J�����S���W��������
        collisionSphere.localCenter = VGet(0, 0, 0);

        // �����蔻�苅�̔��a��������
        collisionSphere.radius = 65.0f;

        // ���������蔻���ݒ�
        collisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, -30.0f, 0.0f));

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    Player::~Player()
    {
        // ���f���̃A�����[�h
        AssetManager::ReleaseMesh(modelHandle);
    }

    void Player::Update(float deltaTime)
    {
        Move(deltaTime);

        RotateCheck();

        shotInterval -= deltaTime;

        Shot();

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

                onGround = true;

                // �����蔻����̉��
                MV1CollResultPolyDimTerminate(collInfo);

                // �����蔻��̍X�V
                CollisionUpdate();
            }
            else
            {
                onGround = false;

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
            // �������Ă�����
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // �������v�Z����
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // �����߂��ʂ��v�Z����
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // ���K������
                    pushBack = VNorm(pushBack);

                    pushBack.y = 1;

                    // �����߂�
                    pos += pushBack * -dif;
                }
                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }

        if (tag == ObjectTag::EnemyBullet)
        {
            if (CollisionPair(collisionSphere, other->GetCollisionSphere()))
            {
                float vx = collisionSphere.worldCenter.x - other->GetCollisionSphere().worldCenter.x;
                float vz = collisionSphere.worldCenter.z - other->GetCollisionSphere().worldCenter.z;
                float r = sqrtf(pow(vx, 2.0f) + pow(vz, 2.0f));

                if (collisionSphere.radius + other->GetCollisionSphere().radius > r)
                {
                    // �������v�Z����
                    float dif = collisionSphere.radius + other->GetCollisionSphere().radius - r;

                    // �����߂��ʂ��v�Z����
                    VECTOR pushBack = other->GetCollisionSphere().worldCenter - collisionSphere.worldCenter;

                    // ���K������
                    pushBack = VNorm(pushBack);

                    // �����߂�
                    pos += pushBack * -dif * 100.0f;
                }

                // �����蔻��̍X�V
                CollisionUpdate();
            }
        }
    }

    void Player::Move(float deltaTime)
    {
        // �J�����������Ă���
        GameObject* camera = GameObjectManager::GetFirstGameObject(ObjectTag::Camera);

        // �J�����̐��ʕ����̈ʒu�x�N�g�����v�Z
        VECTOR front = pos - camera->GetPos();

        // ��������
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

        if (GamePad::GetInput(Button::UP) || 0 < GamePad::GetLeftStickY() || CheckHitKey(KEY_INPUT_W))
        {
            inputVec += UP;
            input = true;
        }

        if (GamePad::GetInput(Button::DOWN) || GamePad::GetLeftStickY() < 0 || CheckHitKey(KEY_INPUT_S))
        {
            inputVec += DOWN;
            input = true;
        }

        if (GamePad::GetInput(Button::LEFT) || GamePad::GetLeftStickX() < 0 || CheckHitKey(KEY_INPUT_A))
        {
            inputVec += LEFT;
            input = true;
        }

        if (GamePad::GetInput(Button::RIGHT) || 0 < GamePad::GetLeftStickX() || CheckHitKey(KEY_INPUT_D))
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

            speed = inputVec + (inputVec * deltaTime * 400.0f);
        }
        else
        {
            speed *= 0.9f;
        }

        pos += speed;

        if (!onGround)
        {
            speed = (VGet(0, -1, 0) * 10.0f);
        }

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

    void Player::Shot()
    {
        if (CheckHitKey(KEY_INPUT_J) && !CheckHitKey(KEY_INPUT_K) && shotInterval < 0)
        {
            shotInterval = 0.25f;
            GameObjectManager::Entry(new NormalBullet(ObjectTag::PlayerBullet, pos, dir));
        }

        if (CheckHitKey(KEY_INPUT_K) && !CheckHitKey(KEY_INPUT_J) && !isCharge)
        {
            isCharge = true;
            GameObjectManager::Entry(new ChargeBullet(ObjectTag::PlayerBullet, pos, dir));
        }

        if (!CheckHitKey(KEY_INPUT_K))
        {
            isCharge = false;
        }
    }
}// namespace My3dApp