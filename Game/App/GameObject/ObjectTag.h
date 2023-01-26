#pragma once

#include <vector>

namespace My3dApp
{
    // ゲーム内のアクター・当たり判定の種類別タグ
    enum class ObjectTag : unsigned char
    {
        Map,
        Player,
        PlayerBullet,
        Enemy,
        EnemyBullet,
        Camera
    };

    constexpr static ObjectTag ObjectTagAll[] =
    {
        ObjectTag::Map,
        ObjectTag::Player,
        ObjectTag::PlayerBullet,
        ObjectTag::Enemy,
        ObjectTag::EnemyBullet,
        ObjectTag::Camera,
    };
}// namespace My3dApp