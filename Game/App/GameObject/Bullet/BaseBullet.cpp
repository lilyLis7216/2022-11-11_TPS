#include "BaseBullet.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="tag">�I�u�W�F�N�g�̎��</param>
    BaseBullet::BaseBullet(ObjectTag tag)
        : GameObject(tag)
    {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    BaseBullet::~BaseBullet()
    {
        // �����Ȃ�
    }
}// namespace My3dApp