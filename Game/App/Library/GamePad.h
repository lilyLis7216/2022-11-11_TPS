#pragma once

#include "DxLib.h"

using namespace std;

namespace My3dApp
{
    /// <summary>
    /// �Q�[���p�b�h�N���X
    /// </summary>
    class GamePad final
    {
    private:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        GamePad();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~GamePad();

        // �Q�[���p�b�h�N���X�̗B��̃C���X�^���X
        static GamePad* instance;

        // �p�b�h�̓��͏��
        static XINPUT_STATE padState;

        // �{�^���̓��͎��ʗp
        static int buttonInput;

    public:
        /// <summary>
        /// �C���X�^���X�̐���
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// �C���X�^���X�̍폜
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// �Q�[���p�b�h�̍X�V
        /// </summary>
        static void Update();

        // �{�^���̗񋓌^�i�}�W�b�N�i���o�[���p�j
        enum ButtonNum
        {
            UP = 0,  // �f�W�^�������{�^����
            DOWN,    // �f�W�^�������{�^����
            LEFT,    // �f�W�^�������{�^����
            RIGHT,   // �f�W�^�������{�^���E
            START,   // START�{�^��
            BACK,    // BACK�{�^��
            LSTICK,  // ���X�e�B�b�N��������
            RSTICK,  // �E�X�e�B�b�N��������
            LB,      // LB�{�^��
            RB,      // RB�{�^��
            NONE1,   // ����U��Ȃ�
            NONE2,   // ����U��Ȃ�
            A,       // A�{�^��
            B,       // B�{�^��
            X,       // X�{�^��
            Y,       // Y�{�^��
        };

        /// <summary>
        /// �{�^���̓��͏�Ԃ̎擾
        /// </summary>
        /// <param name="buttonNumber">�擾�������{�^���̔ԍ�</param>
        /// <returns>���͂���Ă�����true �����łȂ����false</returns>
        static bool GetInput(const int buttonNumber);

        /// <summary>
        /// ���g���K�[�̎擾
        /// </summary>
        /// <returns></returns>
        static const unsigned char GetLeftTrigger() { return padState.LeftTrigger; }

        /// <summary>
        /// �E�g���K�[�̎擾
        /// </summary>
        /// <returns></returns>
        static const unsigned char GetRightTrigger() { return padState.RightTrigger; }

        /// <summary>
        /// ���X�e�B�b�N��X���W
        /// </summary>
        /// <returns></returns>
        static const short GetLeftStickX() { return padState.ThumbLX; }

        /// <summary>
        /// ���X�e�B�b�N��Y���W
        /// </summary>
        /// <returns></returns>
        static const short GetLeftStickY() { return padState.ThumbLY; }

        /// <summary>
        /// �E�X�e�B�b�N��X���W
        /// </summary>
        /// <returns></returns>
        static const short GetRightStickX() { return padState.ThumbRX; }

        /// <summary>
        /// �E�X�e�B�b�N��Y���W
        /// </summary>
        /// <returns></returns>
        static const short GetRightStickY() { return padState.ThumbRY; }
    };

#define Button GamePad::ButtonNum
}/** namespace My3dApp*/