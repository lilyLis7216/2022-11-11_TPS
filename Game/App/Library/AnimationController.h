#pragma once

#include <string>
#include <vector>

namespace My3dApp
{
    class AnimationController final
    {
    public:
        // �A�j���[�V�����p�f�[�^�\���� �A�j���[�V����1��
        struct AnimData
        {
        public:
            /// <summary>
            /// �R���X�g���N�^
            /// </summary>
            AnimData();

            // �A�j���[�V�����n���h��
            int animationHandle;

            // �A�^�b�`����A�j���[�V�����ԍ�
            int animationIndex;

            // �A�j���[�V�����̑��Đ�����
            float animationTotalTime;

            // �A�j���[�V�����Đ����x
            float animationPlayFps;

            // ���[�v�Đ��������邩�ǂ���
            bool isLoopAnimation;
        };

    private:
        // �������Ƃ̃��f���n���h��
        int modelHandle;

        // �ۑ��p�x�N�^�[
        std::vector<AnimData> animDatas;

        // �Đ����̃A�j���[�V����ID
        int nowAnimTypeNum;

        // ��t��̃C���f�b�N�X
        int attachedIndex;

        // �Đ����̃A�j���[�V��������
        float nowAnimTime;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="handle">�A�j���[�V������K�p���郂�f���n���h��</param>
        AnimationController(int handle);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~AnimationController();

        /// <summary>
        /// �A�j���[�V�����̒ǉ�
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="fps"></param>
        /// <param name="isLoop"></param>
        /// <returns></returns>
        int AddAnimation(std::string fileName, float fps = 30.0f, bool isLoop = true);

        /** �A�j���[�V�����̎��Ԃ̃Z�b�g*/
        void AddAnimationTime(float deltaTime);

        /// <summary>
        /// �A�j���[�V�����̍Đ�
        /// </summary>
        /// <param name="id">�Đ��������A�j���[�V����id</param>
        void StartAnimation(int id);

        /// <summary>
        /// �A�j���[�V�����̒�~
        /// </summary>
        void StopAnimation();

        /// <summary>
        /// �Đ������ǂ���
        /// </summary>
        /// <returns>�Đ����Ȃ�true ��~���Ȃ�false</returns>
        bool IsPlaying();

    };
}/** namespace My3dApp*/