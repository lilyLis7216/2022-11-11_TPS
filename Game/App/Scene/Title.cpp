#include "Title.h"
#include "DxLib.h"

namespace My3dApp
{
    Title::Title()
    {
        text = "1.Title";
    }

    Title::~Title()
    {
        /** �����Ȃ�*/
    }

    SceneBase* Title::Update()
    {
        ChangeScene();
        /** �����Ȃ���Ύ��g��Ԃ�*/
        return this;
    }

    void Title::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/