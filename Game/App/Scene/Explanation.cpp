#include "Explanation.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Library/GamePad.h"
#include "Title.h"
#include "../GameObject/Player.h"
#include "../GameObject/Map.h"
#include "../GameObject/Camera.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/EnemyManager.h"
#include "../Library/UserInterface.h"

namespace My3dApp
{
    Explanation::Explanation()
    {
        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        EnemyManager::CreateInstance();

        // ライトの方向を設定
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        // ライトの座標を設定
        SetLightPosition(VGet(100.0f, -10.5f, -50.0f));

        // 遠近法カメラへ切り替え
        SetupCamera_Perspective(1000.0f);

        SetAlpha(255);

        fadeState = FADE_IN;
    }

    Explanation::~Explanation()
    {
        EnemyManager::DeleteInstance();

        GameObjectManager::ReleaseAllObject();
    }

    SceneBase* Explanation::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        if (fadeState == FADE_NONE)
        {
            GameObjectManager::Update(deltaTime);

            EnemyManager::Update(deltaTime, 0, 1);

            GameObjectManager::Collision();

            GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

            if (GamePad::GetButtonState(Button::BACK) == 1 || player->GetPos().y < -500.0f)
            {
                nextScene = TITLE;
                fadeState = FADE_OUT;
            }
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
            GameObjectManager::Update(deltaTime);

            GameObjectManager::Collision();
            if (alpha > 0)
            {
                FadeIn();
                if (alpha <= 0)
                {
                    fadeState = FADE_NONE;
                }
            }
        }

        return retScene;
    }

    void Explanation::Draw()
    {
        GameObjectManager::Draw();

        DrawEffekseer3D();

        SetFontSize(50);
        UserInterface::UIBox(40, 610, 40, 130, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(60, 60, GetColor(255, 255, 255), "Back Button to Title");

        if (fadeState != FADE_NONE)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }
}/** namespace My3dApp*/