#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// �v���C�V�[���i�h���N���X�A�p�����F�V�[���x�[�X�j
    /// </summary>
    class Play : public SceneBase
    {
    private:

        // �^�C�}�[
        float timer;

        /*const int gaugeWidth = 440;
        const int gaugeHeight = 80;
        const int gaugeX = 1410;
        const int gaugeY = 170;*/

        const int gaugeWidth = 440;
        const int gaugeHeight = 80;
        const int gaugeX = 210;
        const int gaugeY = 50;

        static int gaugeValue;
        int gaugeMax = 500;
        int prevComb;

        int countImage[12];

        void GaugeUpdate(float deltaTime);

        int startCount;
        float startCountTimer;
        bool countSE1;
        int endCount;

        int playerBar;

        class GameObject* player;

    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Play();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Play();

        /// <summary>
        /// �v���C�V�[���̍X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        /// <returns>���݂̃V�[���A�܂��͑J�ڗ\��̃V�[��</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// �v���C�V�[���̕`��
        /// </summary>
        void Draw() override;

        static int GetGauge() { return gaugeValue; }
        static void AddGauge(int set) { gaugeValue += set; }
        static void SetMaxGauge() { gaugeValue = 500; }

    };
}// namespace My3dApp