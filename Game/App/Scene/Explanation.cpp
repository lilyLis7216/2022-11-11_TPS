#include "Explanation.h"
#include "DxLib.h"
#include "../Library/GamePad.h"
#include "Title.h"
#include "../GameObject/Player.h"
#include "../GameObject/Map.h"
#include "../GameObject/Camera.h"
#include "../Manager/GameObjectManager.h"

namespace My3dApp
{
    Explanation::Explanation()
    {
        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        // ライトの方向を設定
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        SetLightPosition(VGet(100.0f, -10.5f, -50.0f));

        // 遠近法カメラへ切り替え
        SetupCamera_Perspective(1000.0f);

        SetAlpha(255);

        isFade = true;

        fadeState = FADE_IN;
    }

    Explanation::~Explanation()
    {
        GameObjectManager::ReleaseAllObject();

        //// カメラの位置と向きを設定
        //SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));

        //// 正射影カメラに切り替え
        //SetupCamera_Ortho(1000.0f);
    }

    SceneBase* Explanation::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        GameObjectManager::Update(deltaTime);

        GameObjectManager::Collision();

        //retScene = CheckRetScene(2);

        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (!isFade)
        {
            if (GamePad::GetButtonState(Button::BACK) == 1 /*|| player->GetPos().y < -500.0f*/)
            {
                nextScene = TITLE;
                isFade = true;
                fadeState = FADE_OUT;
            }
        }

        if (fadeState == FADE_NONE)
        {

        }
        else if (fadeState == FADE_OUT)
        {
            if (alpha <= 255)
            {
                FadeOut();
                if (alpha >= 255)
                {
                    if (nextScene == TITLE)
                    {
                        retScene = new Title();
                    }
                }
            }
        }
        else if (fadeState == FADE_IN)
        {
            if (alpha > 0)
            {
                FadeIn();
                if (alpha <= 0)
                {
                    isFade = false;
                    fadeState = FADE_NONE;
                }
            }
        }

        return retScene;
    }

    void Explanation::Draw()
    {
        GameObjectManager::Draw();

        if (isFade)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }
}/** namespace My3dApp*/