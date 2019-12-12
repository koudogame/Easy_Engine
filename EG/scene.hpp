#ifndef INCLUDED_EG_EG_SCENE_HEADER_
#define INCLUDED_EG_EG_SCENE_HEADER_

// �쐬�� : ��

#include "easy_engine.hpp"

BEGIN_EG_EG

class SceneManager;
//
// �V�[���P�ʃN���X
// �������Ɏg�p����l�͊e�V�[���ɂ��قȂ�̂ŁA�������֐��͊e�V�[�����Ƃɗp�ӂ���B
//
class Scene
{
public :
    Scene( SceneManager* Manager );
    virtual ~Scene() = default;
    
    // �X�V����
    void update();
    // �I������
    void finalize();
    // �`�揈��
    void draw();

private :
    SceneManager* manager_;
};

END_EG_EG

#endif // INCLUDED_EG_EG_SCENE_HEADER_
// EOF
