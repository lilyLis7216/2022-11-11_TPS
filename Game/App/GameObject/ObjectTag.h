#pragma once

#include <vector>

namespace My3dApp
{
    // �Q�[�����̃A�N�^�[�E�����蔻��̎�ޕʃ^�O
    enum class ObjectTag : unsigned char
    {
        Map,
        Player,
        PlayerBullet,
        Enemy,
        EnemyBullet,
        Effect,
        Camera,
    };

    constexpr static ObjectTag ObjectTagAll[] =
    {
        ObjectTag::Map,
        ObjectTag::Player,
        ObjectTag::PlayerBullet,
        ObjectTag::Enemy,
        ObjectTag::EnemyBullet,
        ObjectTag::Effect,
        ObjectTag::Camera,
    };
}// namespace My3dApp