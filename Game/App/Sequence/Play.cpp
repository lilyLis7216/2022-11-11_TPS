#include "Play.h"
#include "DxLib.h"

namespace My3dApp
{
    Play::Play()
        :SceneBase(SceneType::Scene_Play)
    {
        text = "3.Play";
    }

    Play::~Play()
    {
        /** èàóùÇ»Çµ*/
    }

    SceneType Play::Update()
    {
        nowSceneType = SceneType::Scene_Play;

        InputCheck();

        return nowSceneType;
    }

    void Play::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/