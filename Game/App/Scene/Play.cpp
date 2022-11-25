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
        /** ˆ—‚È‚µ*/
    }

    SceneBase* Play::Update()
    {
        ChangeScene();
        /** ‰½‚à‚È‚¯‚ê‚Î©g‚ğ•Ô‚·*/
        return this;
    }

    void Play::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/