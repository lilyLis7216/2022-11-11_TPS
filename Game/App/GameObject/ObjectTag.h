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
        PlayerBulletCharge,
        Enemy,
        EnemyBullet,
        EnemyBulletS,
        EnemyBulletM,
        EnemyBulletL,
        Effect,
        Camera,
    };

    constexpr static ObjectTag ObjectTagAll[] =
    {
        ObjectTag::Map,
        ObjectTag::Player,
        ObjectTag::PlayerBullet,
        ObjectTag::PlayerBulletCharge,
        ObjectTag::Enemy,
        ObjectTag::EnemyBullet,
        ObjectTag::EnemyBulletS,
        ObjectTag::EnemyBulletM,
        ObjectTag::EnemyBulletL,
        ObjectTag::Effect,
        ObjectTag::Camera,
    };
}// namespace My3dApp