#include "GameObject.h"

namespace My3dApp
{
    GameObject::GameObject(ObjectTag tag)
        : GameObject(tag, VGet(0, 0, 0))
    {
    }

    GameObject::GameObject(ObjectTag tag, VECTOR pos)
        : tag(tag)
        , modelHandle(-1)
        , isVisible(true)
        , isAlive(true)
        , onGround(true)
        , collisionType()
        , collisionLine()
        , collisionSphere()
        , collisionCapsule()
        , collisionModel()
        , damagePar(0.0f)
    {
        this->pos = pos;
        dir = VGet(0, 1, 0);
    }

    GameObject::~GameObject()
    {
        // ÉÇÉfÉãÇÃå„énññ
        if (modelHandle != -1)
        {
            MV1DeleteModel(modelHandle);
            modelHandle = -1;
        }
    }

    void GameObject::Draw()
    {
        // èàóùÇ»Çµ
    }

    void GameObject::DrawCollider()
    {
        // ê¸ï™ìñÇΩÇËîªíËÇÃï`âÊ
        DrawLine3D(collisionLine.worldStart, collisionLine.worldEnd, GetColor(255, 255, 0));

        // ãÖëÃìñÇΩÇËîªíËÇÃï`âÊ
        DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);

        // ÉJÉvÉZÉãìñÇΩÇËîªíËÇÃï`âÊ
        DrawCapsule3D(collisionCapsule.worldStart, collisionCapsule.worldEnd, collisionCapsule.radius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);

        // ìñÇΩÇËîªíËÉÇÉfÉãÇ™Ç†ÇÈèÍçá
        if (collisionModel != -1)
        {
            // îºìßñæÇ…ÇµÇƒï`âÊÇ∑ÇÈ
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(collisionModel);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }

    void GameObject::CollisionUpdate()
    {
        collisionSphere.Move(pos);

        collisionLine.Move(pos);

        collisionCapsule.Move(pos);

        // ÉÇÉfÉãÇÃìñÇΩÇËîªíËèÓïÒÇçƒç\íz
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);

            MV1SetupCollInfo(collisionModel);
        }
    }
    void GameObject::DamageParView()
    {
        VECTOR screenPos = ConvWorldPosToScreenPos(pos);

        SetFontSize(25);

        int cr = GetColor(255, 255, 255);

        if (damagePar >= 100)
        {
            cr = GetColor(161, 21, 8);
        }
        else if (damagePar >= 80)
        {
            cr = GetColor(219, 78, 10);
        }
        else if (damagePar >= 60)
        {
            cr = GetColor(255, 142, 61);
        }
        else if (damagePar >= 40)
        {
            cr = GetColor(252, 167, 10);
        }
        else if (damagePar >= 20)
        {
            cr = GetColor(254, 222, 10);
        }

        DrawFormatString((int)screenPos.x - 20, (int)screenPos.y - 50, cr, "%1.0fÅì", damagePar);
    }
}// namespace My3dApp