#pragma once

#include <string>
#include <vector>

namespace My3dApp
{
    class AnimationController final
    {
    public:
        /** アニメーション用データ構造体 アニメーション1個分*/
        struct AnimData
        {
        public:
            AnimData();

            /** アニメーションハンドル*/
            int animationHandle;

            /** アタッチするアニメーション番号*/
            int animationIndex;

            /** アニメーションの総再生時間*/
            float animationTotalTime;

            /** アニメーション再生速度*/
            float animationPlayFps;

            /** ループ再生を許可するかどうか*/
            bool isLoopAnimation;
        };

    private:
        /** おおもとのモデルハンドル*/
        int modelHandle;

        std::vector<AnimData> animDatas;

        /** 再生中のアニメーションID*/
        int nowAnimTypeNum;

        /** 取付後のインデックス*/
        int attachedIndex;

        /** 再生中のアニメーション時刻*/
        float nowAnimTime;

    public:
        /** コンストラクタ*/
        AnimationController(int handle);

        /** デストラクタ*/
        ~AnimationController();

        /** アニメーションの追加*/
        int AddAnimation(std::string fileName, float fps = 30.0f, bool isLoop = true);

        /** アニメーションの時間のセット*/
        void AddAnimationTime(float deltaTime);

        /** アニメーションの再生*/
        void StartAnimation(int id);

        /** アニメーションの停止*/
        void StopAnimation();

        /** 再生中かどうか*/
        bool IsPlaying();

    };

}/** namespace My3dApp*/