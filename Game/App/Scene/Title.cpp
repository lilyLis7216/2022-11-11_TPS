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
        /** ˆ—‚È‚µ*/
    }

    SceneBase* Title::Update()
    {
        ChangeScene();
        /** ‰½‚à‚È‚¯‚ê‚Î©g‚ğ•Ô‚·*/
        return this;
    }

    void Title::Draw()
    {
        CheckNowScene();
    }

}/** namespace My3dApp*/