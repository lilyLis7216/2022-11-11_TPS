#include "Play.h"
#include "DxLib.h"

namespace My3dApp
{
    Play::Play()
    {
        text = "3.Play";
    }

    Play::~Play()
    {
        /** �����Ȃ�*/
    }

    SceneBase* Play::Update()
    {
        ChangeScene();
        /** �����Ȃ���Ύ��g��Ԃ�*/
        return this;
    }

    void Play::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/