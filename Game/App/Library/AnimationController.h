#pragma once

#include <string>
#include <vector>

namespace My3dApp
{
    class AnimationController final
    {
    public:
        // アニメーション用データ構造体 アニメーション1個分
        struct AnimData
        {
        public:
            /// <summary>
            /// コンストラクタ
            /// </summary>
            AnimData();

            // アニメーションハンドル
            int animationHandle;

            // アタッチするアニメーション番号
            int animationIndex;

            // アニメーションの総再生時間
            float animationTotalTime;

            // アニメーション再生速度
            float animationPlayFps;

            // ループ再生を許可するかどうか
            bool isLoopAnimation;
        };

    private:
        // おおもとのモデルハンドル
        int modelHandle;

        // 保存用ベクター
        std::vector<AnimData> animDatas;

        // 再生中のアニメーションID
        int nowAnimTypeNum;

        // 取付後のインデックス
        int attachedIndex;

        // 再生中のアニメーション時刻
        float nowAnimTime;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="handle">アニメーションを適用するモデルハンドル</param>
        AnimationController(int handle);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~AnimationController();

        /// <summary>
        /// アニメーションの追加
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="fps"></param>
        /// <param name="isLoop"></param>
        /// <returns></returns>
        int AddAnimation(std::string fileName, float fps = 30.0f, bool isLoop = true);

        /** アニメーションの時間のセット*/
        void AddAnimationTime(float deltaTime);

        /// <summary>
        /// アニメーションの再生
        /// </summary>
        /// <param name="id">再生したいアニメーションid</param>
        void StartAnimation(int id);

        /// <summary>
        /// アニメーションの停止
        /// </summary>
        void StopAnimation();

        /// <summary>
        /// 再生中かどうか
        /// </summary>
        /// <returns>再生中ならtrue 停止中ならfalse</returns>
        bool IsPlaying();

    };
}/** namespace My3dApp*/