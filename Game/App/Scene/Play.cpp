#include "Play.h"
#include "DxLib.h"
#include "../GameObject/Player.h"
#include "../Library/DebugGrid.h"

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

        DrawGrid(3000, 30);

        player->Draw();
    }

}/** namespace My3dApp*/