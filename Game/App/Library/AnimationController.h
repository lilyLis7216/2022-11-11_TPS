#pragma once

#include <string>
#include <vector>

namespace My3dApp
{
    class AnimationController final
    {
    public:
        /** �A�j���[�V�����p�f�[�^�\���� �A�j���[�V����1��*/
        struct AnimData
        {
        public:
            AnimData();

            /** �A�j���[�V�����n���h��*/
            int animationHandle;

            /** �A�^�b�`����A�j���[�V�����ԍ�*/
            int animationIndex;

            /** �A�j���[�V�����̑��Đ�����*/
            float animationTotalTime;

            /** �A�j���[�V�����Đ����x*/
            float animationPlayFps;

            /** ���[�v�Đ��������邩�ǂ���*/
            bool isLoopAnimation;
        };

    private:
        /** �������Ƃ̃��f���n���h��*/
        int modelHandle;

        std::vector<AnimData> animDatas;

        /** �Đ����̃A�j���[�V����ID*/
        int nowAnimTypeNum;

        /** ��t��̃C���f�b�N�X*/
        int attachedIndex;

        /** �Đ����̃A�j���[�V��������*/
        float nowAnimTime;

    public:
        /** �R���X�g���N�^*/
        AnimationController(int handle);

        /** �f�X�g���N�^*/
        ~AnimationController();

        /** �A�j���[�V�����̒ǉ�*/
        int AddAnimation(std::string fileName, float fps = 30.0f, bool isLoop = true);

        /** �A�j���[�V�����̎��Ԃ̃Z�b�g*/
        void AddAnimationTime(float deltaTime);

        /** �A�j���[�V�����̍Đ�*/
        void StartAnimation(int id);

        /** �A�j���[�V�����̒�~*/
        void StopAnimation();

        /** �Đ������ǂ���*/
        bool IsPlaying();

    };

}/** namespace My3dApp*/