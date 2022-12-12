#include "AnimationController.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    AnimationController::AnimationController(int handle)
        : modelHandle(handle)
        , nowAnimTypeNum(-1)
        , nowAnimTime(0.0f)
        , attachedIndex(0)
    {
    }

    AnimationController::~AnimationController()
    {
    }

    int AnimationController::AddAnimation(std::string fileName, float fps, bool isLoop)
    {
        AnimData anim;
        anim.animationPlayFps = fps;
        anim.isLoopAnimation = isLoop;

        // �A�j���[�V�����f�[�^�ǂݍ���
        anim.animationHandle = AssetManager::GetAnimation(fileName.c_str());
        if (anim.animationHandle == -1)
        {
            return -1;
        }
        anim.animationIndex = MV1GetAnimNum(anim.animationHandle) - 1;

        attachedIndex = MV1AttachAnim(modelHandle, anim.animationIndex, anim.animationHandle, TRUE);
        anim.animationTotalTime = MV1GetAnimTotalTime(anim.animationHandle, anim.animationIndex);

        // �A�j���[�V��������
        int test;
        test = MV1DetachAnim(modelHandle, attachedIndex);

        // �����ɃA�j���[�V�����f�[�^�ǉ�
        animDatas.push_back(anim);

        // vector�ɓ���Y�����ԍ���Ԃ�
        return static_cast<int>(animDatas.size() - 1);
    }

    void AnimationController::AddAnimationTime(float deltaTime)
    {
        nowAnimTime += deltaTime * animDatas[nowAnimTypeNum].animationPlayFps;

        // ���[�v�Đ�
        if (animDatas[nowAnimTypeNum].isLoopAnimation && nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            nowAnimTime = 0.0f;
        }

        int test;
        test = MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

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

    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    bool AnimationController::IsPlaying()
    {
        if (animDatas[nowAnimTypeNum].isLoopAnimation && nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            return false;
        }
        return true;
    }

    AnimationController::AnimData::AnimData()
        : animationHandle(-1)
        , animationIndex(-1)
        , animationTotalTime(-1.0f)
        , animationPlayFps(0.0f)
        , isLoopAnimation(false)
    {
    }
}/** namespace My3dApp*/