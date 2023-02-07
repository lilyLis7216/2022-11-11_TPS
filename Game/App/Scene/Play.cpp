#include "Play.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "../Manager/GameManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/EnemyManager.h"
#include "../GameObject/Player.h"
#include "../GameObject/Camera.h"
#include "../GameObject/Map.h"
#include "../GameObject/Enemy/NormalEnemy.h"
#include "../Library/DebugGrid.h"
#include "../Library/UserInterface.h"
#include "Result.h"

namespace My3dApp
{
    Play::Play()
        : timer(60.0f)
        , prevComb(0)
    {
        text = "3.Play";

        bgImage = -1;

        EnemyManager::CreateInstance();

        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        GameObjectManager::Entry(new NormalEnemy(VGet(0, 200, 1000)));
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();

        EnemyManager::DeleteInstance();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        timer -= deltaTime;

        prevComb = GameManager::GetCombo();

        SceneBase* retScene = this;

        EnemyManager::Update(deltaTime);

        GameObjectManager::Update(deltaTime);

        // エフェクシアの更新
        UpdateEffekseer3D();

        GameObjectManager::Collision();

        GaugeUpdate(deltaTime);

        retScene = CheckRetScene(3);

        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (timer < 0 || player->GetPos().y < -500.0f)
        {
            retScene = new Result();
        }

        return retScene;
    }

    void Play::Draw()
    {
        GameObjectManager::Draw();

        DrawEffekseer3D();

        SetFontSize(50);

        // タイマーの表示
        UserInterface::UIBox(760, 1140, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(820, 70, GetColor(255, 255, 255), "Time:%0.1f", timer);

        // スコアの表示
        UserInterface::UIBox(1460, 1860, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(1480, 70, GetColor(255, 255, 255), "SCORE : %3.0f", (float)GameManager::GetScore());

        // コンボの表示
        UserInterface::UIBox(1460, 1860, 160, 260, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(1480, 180, GetColor(255, 255, 255), "COMBO : %3.0f", (float)GameManager::GetCombo());

        int gaugeFillWidth = gaugeWidth * gaugeValue / gaugeMax;
        UserInterface::UIBox(gaugeX, gaugeX + gaugeFillWidth, gaugeY, gaugeY + gaugeHeight, 0, GetColor(255, 255, 255), 0);

        //CheckNowScene();
    }

    void Play::GaugeUpdate(float deltaTime)
    {
        gaugeValue -= 1;
        if (prevComb != GameManager::GetCombo())
        {
            gaugeValue = gaugeMax;
        }

        if (gaugeValue < 0)
        {
            gaugeValue = 0;
            GameManager::ResetCombo();
        }
    }
}// namespace My3dApp