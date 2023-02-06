#include "UserInterface.h"
#include "DxLib.h"

namespace My3dApp
{
    UserInterface* UserInterface::instance = nullptr;

    UserInterface::UserInterface()
    {
        instance = this;
        // �t�H���g�̓ǂݍ��݂�����������
        if (AddFontResourceEx("../asset/font/851CHIKARA-DZUYOKU_kanaA_004.ttf", FR_PRIVATE, NULL) > 0)
        {
            ChangeFont("851�`�J���d���N-����A", DX_CHARSET_DEFAULT);
        }
        // ���s������
        else
        {
            // �G���[���b�Z�[�W��\������
            MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
        }
    }

    UserInterface::~UserInterface()
    {
        // �t�H���g�̍폜������������
        if (RemoveFontResourceEx("../asset/font/851CHIKARA-DZUYOKU_kanaA_004.ttf", FR_PRIVATE, NULL))
        {
            // �����Ȃ�
        }
        // ���s������
        else
        {
            // �G���[���b�Z�[�W��\������
            MessageBox(NULL, "remove failure", "", MB_OK);
        }
    }

    void UserInterface::CreateInstance()
    {
        if (!instance)
        {
            instance = new UserInterface();
        }
    }

    void UserInterface::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void UserInterface::UIText(int x, int y, int color, const char* str, float num)
    {
        DrawFormatString(x, y, color, str, num);
    }

    void UserInterface::UIText(int x, int y, int color, const char* str)
    {
        DrawString(x, y, str, color);
    }

    void UserInterface::UIBox(int x1, int x2, int y1, int y2, int frameSize, int mainCr, int frameCr)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

        // �x�[�X
        DrawBox(x1, y1, x2, y2, mainCr, TRUE);

        // ���
        DrawLine(x1 + frameSize, y1 + frameSize / 2, x2 - frameSize, y1 + frameSize / 2, frameCr, frameSize);

        // ����
        DrawLine(x1 + frameSize, y2 - frameSize / 2, x2 - frameSize, y2 - frameSize / 2, frameCr, frameSize);

        // ����
        DrawLine(x1 + frameSize / 2, y1, x1 + frameSize / 2, y2, frameCr, frameSize);

        // �E��
        DrawLine(x2 - frameSize / 2, y1, x2 - frameSize / 2, y2, frameCr, frameSize);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}// namespace My3dApp