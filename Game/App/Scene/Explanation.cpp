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
    }

    Explanation::~Explanation()
    {
        GameObjectManager::ReleaseAllObject();
    }

    SceneBase* Explanation::Update(float deltaTime)
    {
        SceneBase* retScene = this;

        GameObjectManager::Update(deltaTime);

        GameObjectManager::Collision();

        retScene = CheckRetScene(2);

        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        if (GamePad::GetButtonState(Button::BACK) == 1 || player->GetPos().y < -500.0f)
        {
            retScene = new Title();
        }

        return retScene;
    }

    void Explanation::Draw()
    {
        GameObjectManager::Draw();

        /*DrawGraph(0, 0, bgImage, FALSE);

        CheckNowScene();*/
    }
}/** namespace My3dApp*/