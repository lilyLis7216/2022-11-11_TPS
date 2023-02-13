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
    int Play::gaugeValue = 0;

    Play::Play()
        : timer(60.0f)
        , prevComb(0)
    {
        EnemyManager::CreateInstance();

        GameObjectManager::Entry(new Player());

        GameObjectManager::Entry(new Camera(1000, -1000));

        GameObjectManager::Entry(new Map(VGet(0, 0, 0)));

        GameObjectManager::Entry(new NormalEnemy(VGet(0, 200, 1000)));

        LoadDivGraph("../asset/image/num.png", 12, 6, 2, 64, 64, countImage);

        // ライトの方向を設定
        SetLightDirection(VGet(-1.5f, -10.5f, 0.5f));

        SetLightPosition(VGet(100.0f, -10.5f, -50.0f));

        // 遠近法カメラへ切り替え
        SetupCamera_Perspective(1000.0f);

        gaugeValue = 0;
    }

    Play::~Play()
    {
        GameObjectManager::ReleaseAllObject();

        EnemyManager::DeleteInstance();
    }

    SceneBase* Play::Update(float deltaTime)
    {
        timer -= deltaTime;

        SceneBase* retScene = this;

        EnemyManager::Update(deltaTime, timer);

        GameObjectManager::Update(deltaTime);

        // エフェクシアの更新
        UpdateEffekseer3D();

        GameObjectManager::Collision();

        GaugeUpdate(deltaTime);

        retScene = CheckRetScene(3);

        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (timer <= 0.1 || player->GetPos().y < -500.0f)
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
        UserInterface::UIBox(740, 1140, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(800, 70, GetColor(255, 255, 255), "Time:%0.1f", timer);

        // スコアの表示
        UserInterface::UIBox(1200, 1660, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        UserInterface::UIText(1240, 70, GetColor(255, 255, 255), "SCORE : %4.0f", (float)GameManager::GetScore());

        // コンボの表示
        /*UserInterface::UIBox(1400, 1860, 160, 260, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        int gaugeFillWidth = gaugeWidth * gaugeValue / gaugeMax;
        UserInterface::UIBox(gaugeX, gaugeX + gaugeFillWidth, gaugeY, gaugeY + gaugeHeight, 0, GetColor(255, 140, 0), 0);
        UserInterface::UIText(1440, 190, GetColor(255, 255, 255), "COMBO : %4.0f", (float)GameManager::GetCombo());*/

        // コンボの表示
        UserInterface::UIBox(200, 660, 40, 140, 10, GetColor(0, 0, 0), GetColor(0, 0, 255));
        int gaugeFillWidth = gaugeWidth * gaugeValue / gaugeMax;
        UserInterface::UIBox(gaugeX, gaugeX + gaugeFillWidth, gaugeY, gaugeY + gaugeHeight, 0, GetColor(255, 140, 0), 0);

        if (gaugeValue > 0)
        {
            UserInterface::UIText(220, 70, GetColor(255, 255, 255), "SCORE BONUS");
        }

        if (timer < 11 && timer >= 0)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
            SetDrawMode(DX_DRAWMODE_BILINEAR);
            DrawRotaGraph(960, 540, 10.0f, 0, countImage[(int)timer], TRUE);
            SetDrawMode(DX_DRAWMODE_NEAREST);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }

    void Play::GaugeUpdate(float deltaTime)
    {
        gaugeValue -= 1;

        if (gaugeValue < 0)
        {
            gaugeValue = 0;
        }

        if (gaugeValue > gaugeMax)
        {
            gaugeValue = gaugeMax;
        }
    }
}// namespace My3dApp