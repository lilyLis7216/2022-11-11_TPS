#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// ���U���g�V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class Result : public SceneBase
    {
    private:
        int resultModel;

        int backModel;

        int exitModel;

        const float selectSize = 1.0f;

        const float notSelectSize = 0.75f;

        int selectState;

        struct Star
        {
            int model;
            bool valid = false;
            float rotate = 0.0f;
            bool canRotate = true;
        };

        Star leftStar;

        Star middleStar;

        Star rightStar;

        Star aster;

        enum SelectState
        {
            BACK = 0,
            EXIT,
        };

        float nextStar;

        void StarUpdate(float deltaTime);

        float rotateCount;

        void MoveModel(float deltaTime);

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Result();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Result();

        /// <summary>
        /// ���U���g�V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// ���U���g�V�[���̕`��
        /// </summary>
        void Draw() override;

    };
}// namespace My3dApp