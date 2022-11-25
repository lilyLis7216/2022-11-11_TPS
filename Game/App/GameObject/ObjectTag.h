#pragma once
#include <vector>

namespace My3dApp
{
    /** �Q�[�����̃A�N�^�[�E�����蔻��̎�ޕʃ^�O*/
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