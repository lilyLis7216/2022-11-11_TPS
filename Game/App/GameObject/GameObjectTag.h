#pragma once
#include <vector>

namespace My3dApp
{
    /** ゲーム内のアクター・当たり判定の種類別タグ*/
    enum class ObjectTag : unsigned char
    {
        Player,
        PlayerBullet,
        Enemy,
        EnemyBullet,
    };

    constexpr static ObjectTag ObjectTagAll[] =
    {
        ObjectTag::Player,
        ObjectTag::PlayerBullet,
        ObjectTag::Enemy,
        ObjectTag::EnemyBullet,
    };

}/** namespace My3dApp*/