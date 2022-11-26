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
        /** èàóùÇ»Çµ*/
    }

    SceneBase* Play::Update()
    {
        SceneBase* retScene = this;

        retScene = CheckRetScene(3);

        return retScene;
    }

    void Play::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/