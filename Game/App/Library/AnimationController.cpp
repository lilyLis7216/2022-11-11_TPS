#include "AnimationController.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    /**
    * �R���X�g���N�^
    * 
    * @param[in] modelHandle �A�j���[�V������K�p���郂�f���n���h��
    */
    AnimationController::AnimationController(int handle)
        : modelHandle(handle)
        , nowAnimTypeNum(-1)
        , nowAnimTime(0.0f)
        , attachedIndex(0)
    {
    }

    /**
    * �f�X�g���N�^
    */
    AnimationController::~AnimationController()
    {
    }

    /**
    * �A�j���[�V�����̒ǉ�
    */
    int AnimationController::AddAnimation(std::string fileName, float fps, bool isLoop)
    {
        AnimData anim;
        anim.animationPlayFps = fps;
        anim.isLoopAnimation = isLoop;

        /** �A�j���[�V�����f�[�^�ǂݍ���*/
        anim.animationHandle = AssetManager::GetAnimation(fileName.c_str());
        if (anim.animationHandle == -1)
        {
            return -1;
        }
        anim.animationIndex = MV1GetAnimNum(anim.animationHandle) - 1;

        attachedIndex = MV1AttachAnim(modelHandle, anim.animationIndex, anim.animationHandle, TRUE);
        anim.animationTotalTime = MV1GetAnimTotalTime(anim.animationHandle, anim.animationIndex);

        /** �A�j���[�V��������*/
        int test;
        test = MV1DetachAnim(modelHandle, attachedIndex);

        /** �����ɃA�j���[�V�����f�[�^�ǉ�*/
        animDatas.push_back(anim);

        /** vector�ɓ���Y�����ԍ���Ԃ�*/
        return static_cast<int>(animDatas.size() - 1);
    }

    /**
    * �A�j���[�V�����̑���������ݒ�A
    * 
    * @param[in] deltaTime 1�t���[���̌o�ߎ��� 
    * 
    * @details StartAnimation�Őݒ肳�ꂽ�A�j���[�V�����̍Đ���i�߂�B
    * �}�C�t���[��AddAnimationTime���Ăяo���K�v������B
    */
    void AnimationController::AddAnimationTime(float deltaTime)
    {
        nowAnimTime += deltaTime * animDatas[nowAnimTypeNum].animationPlayFps;

        /** ���[�v�Đ�*/
        if (animDatas[nowAnimTypeNum].isLoopAnimation && nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            nowAnimTime = 0.0f;
        }

        int test;
        test = MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * �A�j���[�V�����̍Đ�
    * 
    * @param[in] id �Đ��������A�j���[�V����id
    * 
    * @details id�Ŏw�肵���A�j���[�V�������Đ�����
    * �����A�j���[�V�������w�肳�ꂽ�ꍇ�A�͂��߂���Đ�����
    */
    void AnimationController::StartAnimation(int id)
    {
        /** �ȑO�ƈႤ�A�j���[�V�������������x�f�^�b�`*/
        if (id != nowAnimTypeNum)
        {
            if (nowAnimTypeNum != -1)
            {
                MV1DetachAnim(modelHandle, attachedIndex);
            }

            /** �V�K�A�j���[�V�������Z�b�g*/
            nowAnimTypeNum = id;
            attachedIndex = MV1AttachAnim(modelHandle, animDatas[id].animationIndex, 
                animDatas[nowAnimTypeNum].animationHandle, TRUE);
        }

        nowAnimTime = 0.0f;
        MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * �A�j���[�V�����̒�~
    * 
    * @details �w�肳�ꂽ�A�j���[�V�������I�������ŃX�g�b�v����
    * �Đ��r���̃|�[�Y�Ŏ~�܂�Ȃ����Ƃɒ��ӁB���[�v�Đ��w��̃A�j���[�V�����͖��������B
    */
    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    /**
    * �A�j���[�V�������Đ������ǂ���
    * 
    * @return bool true:�Đ��� false:��~��
    * 
    * @details �w�肳��Ă���A�j���[�V�������Đ������ǂ�����Ԃ�
    * ���[�v�w�肳�ꂽ���̂͏��true��Ԃ��B
    */
    bool AnimationController::IsPlaying()
    {
        if (animDatas[nowAnimTypeNum].isLoopAnimation && nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            return false;
        }
        return true;
    }

    /**
    * �A�j���\�V�����f�[�^�\���� �R���X�g���N�^
    */
    AnimationController::AnimData::AnimData()
        : animationHandle(-1)
        , animationIndex(-1)
        , animationTotalTime(-1.0f)
        , animationPlayFps(0.0f)
        , isLoopAnimation(false)
    {
    }
}/** namespace My3dApp*/