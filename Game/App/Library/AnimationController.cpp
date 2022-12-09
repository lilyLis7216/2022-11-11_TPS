#include "AnimationController.h"
#include "DxLib.h"
#include "../Manager/AssetManager.h"

namespace My3dApp
{
    /**
    * コンストラクタ
    * 
    * @param[in] modelHandle アニメーションを適用するモデルハンドル
    */
    AnimationController::AnimationController(int handle)
        : modelHandle(handle)
        , nowAnimTypeNum(-1)
        , nowAnimTime(0.0f)
        , attachedIndex(0)
    {
    }

    /**
    * デストラクタ
    */
    AnimationController::~AnimationController()
    {
    }

    /**
    * アニメーションの追加
    */
    int AnimationController::AddAnimation(std::string fileName, float fps, bool isLoop)
    {
        AnimData anim;
        anim.animationPlayFps = fps;
        anim.isLoopAnimation = isLoop;

        /** アニメーションデータ読み込み*/
        anim.animationHandle = AssetManager::GetAnimation(fileName.c_str());
        if (anim.animationHandle == -1)
        {
            return -1;
        }
        anim.animationIndex = MV1GetAnimNum(anim.animationHandle) - 1;

        attachedIndex = MV1AttachAnim(modelHandle, anim.animationIndex, anim.animationHandle, TRUE);
        anim.animationTotalTime = MV1GetAnimTotalTime(anim.animationHandle, anim.animationIndex);

        /** アニメーション解除*/
        int test;
        test = MV1DetachAnim(modelHandle, attachedIndex);

        /** 末尾にアニメーションデータ追加*/
        animDatas.push_back(anim);

        /** vectorに入る添え字番号を返す*/
        return static_cast<int>(animDatas.size() - 1);
    }

    /**
    * アニメーションの増分時刻を設定、
    * 
    * @param[in] deltaTime 1フレームの経過時間 
    * 
    * @details StartAnimationで設定されたアニメーションの再生を進める。
    * マイフレームAddAnimationTimeを呼び出す必要がある。
    */
    void AnimationController::AddAnimationTime(float deltaTime)
    {
        nowAnimTime += deltaTime * animDatas[nowAnimTypeNum].animationPlayFps;

        /** ループ再生*/
        if (animDatas[nowAnimTypeNum].isLoopAnimation && nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            nowAnimTime = 0.0f;
        }

        int test;
        test = MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * アニメーションの再生
    * 
    * @param[in] id 再生したいアニメーションid
    * 
    * @details idで指定したアニメーションを再生する
    * 同じアニメーションが指定された場合、はじめから再生する
    */
    void AnimationController::StartAnimation(int id)
    {
        /** 以前と違うアニメーションが来たら一度デタッチ*/
        if (id != nowAnimTypeNum)
        {
            if (nowAnimTypeNum != -1)
            {
                MV1DetachAnim(modelHandle, attachedIndex);
            }

            /** 新規アニメーションをセット*/
            nowAnimTypeNum = id;
            attachedIndex = MV1AttachAnim(modelHandle, animDatas[id].animationIndex, 
                animDatas[nowAnimTypeNum].animationHandle, TRUE);
        }

        nowAnimTime = 0.0f;
        MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * アニメーションの停止
    * 
    * @details 指定されたアニメーションが終了時刻でストップする
    * 再生途中のポーズで止まらないことに注意。ループ再生指定のアニメーションは無視される。
    */
    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    /**
    * アニメーションが再生中かどうか
    * 
    * @return bool true:再生中 false:停止中
    * 
    * @details 指定されているアニメーションが再生中かどうかを返す
    * ループ指定されたものは常にtrueを返す。
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
    * アニメ―ションデータ構造体 コンストラクタ
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