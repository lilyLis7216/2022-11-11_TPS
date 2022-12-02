#include "Play.h"
#include "DxLib.h"
#include "../GameObject/Player.h"

namespace My3dApp
{
    Play::Play()
    {
        text = "3.Play";
        player = new Player();
    }

    Play::~Play()
    {
        delete player;
    }

    SceneBase* Play::Update(float deltaTime)
    {
        SceneBase* retScene = this;
        
        player->Update(deltaTime);

        retScene = CheckRetScene(3);

        return retScene;
    }

    void Play::Draw()
    {
        CheckNowScene();

        player->Draw();
    }

}/** namespace My3dApp*/