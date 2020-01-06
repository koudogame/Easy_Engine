#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_
// �쐬�� : ��
#include "easy_engine.hpp"

BEGIN_EG_EG
class SceneManager;

//
// �V�[���P�ʃN���X
// �������Ɏg�p����l�͊e�V�[���ɂ��قȂ邱�Ƃ�z�肵�āA�������֐��͒�`���Ă��܂���B
// �e�h���N���X�́A�e�X�������p�̊֐����`���ĉ������B
//
class Scene
{
public :
    Scene( SceneManager* Manager ) :
        manager_( Manager )
    {}
    virtual ~Scene() = default;
    
    // �X�V����
    virtual void update() = 0;
    // �I������
    virtual void finalize() = 0;
    // �`�揈��
    virtual void draw() = 0;

private :
    SceneManager* manager_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_HEADER_
// EOF
