#pragma once

#include <vector>

namespace My3dApp
{
    // �Q�[�����̃A�N�^�[�E�����蔻��̎�ޕʃ^�O
    enum class ObjectTag : unsigned char
    {
        Player,
        PlayerBullet,
        Enemy,
        EnemyBullet,
        Map,
        Camera
    };

    constexpr static ObjectTag ObjectTagAll[] =
    {
        ObjectTag::Player,
        ObjectTag::PlayerBullet,
        ObjectTag::Enemy,
        ObjectTag::EnemyBullet,
        ObjectTag::Map,
        ObjectTag::Camera,
    };
}// namespace My3dApp