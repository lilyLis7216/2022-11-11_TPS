#pragma once

namespace Sequence
{
    /** �V�[���̎��*/
    enum class SceneType
    {
        Scene_Title,
        Scene_StageSelect,
        Scene_Play,
        Scene_Result,
        Scene_Exit, 
    };

    /**
    * �V�[���̊��N���X
    * �������z�֐��������Ă��钊�ۃN���X
    */
    class SceneBase
    {
    protected:
        /** ���݂̃V�[���̎��*/
        SceneType nowSceneType;

    public:
        /**
        * �R���X�g���N�^
        * 
        * @param[in] sceneType �V�[���̎��
        */
        SceneBase(SceneType sceneType);

        /** ���z�f�X�g���N�^*/
        virtual ~SceneBase();

        /**
        * �X�V�����i�������z�֐��j
        * 
        * @return �V�[���̎��
        */
        virtual SceneType Update() = 0;

        /** �`�揈���i�������z�֐��j*/
        virtual void Draw() = 0;
    };

}/** namespace Sequence*/