#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_

// �쐬�� : ��

#include <stack>
#include "easy_engine.hpp"

BEGIN_EG_EG

class Scene;

//
// �V�[���Ǘ��N���X
//
// �V���O���g���N���X�B�C���X�^���X�ւ̃A�N�Z�X�� instance�֐����g�p����B
// �V�[���̈����� stack(������o��) �ł���B 
// �A�N�e�B�u�ȃV�[���͍Ō�ɒǉ����ꂽ�V�[���B
// update�֐� �y�� draw�֐� �̓��X�g�ɕۑ����Ă���S�ẴV�[���ɑ΂��Ċ֐��̌Ăяo�����s���B
//
class SceneManager
{
public :
    // �C���X�^���X�ւ̃A�h���X���擾
    static SceneManager* instance() { static SceneManager i; return &i; }

    //
    // �ێ����Ă���V�[����update�֐����Ăяo���B
    //
    void update();
    //
    // �ێ����Ă���V�[����draw�֐����Ăяo���B
    //
    void draw();

    //
    // �A�N�e�B�u�ȃV�[�����擾����
    //
    inline Scene* getActive() const { return scene_list_.back(); }
    //
    // �V�[����ǉ�����B
    // ���̎��ǉ������ʒu�� ��ԍŌ�
    // 
    // in Push : �ǉ�����V�[��
    //
    inline void push( Scene* Push ) { scene_list_.push_back( Push ); }
    //
    // �V�[�������O����B
    // ���̎����O�̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���B
    //
    void pop();
    //
    // �V�[�������ւ���B
    // ���̎�����ւ��̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���B
    //
    void swap( Scene* Swap );

private :
    std::stack<Scene*> scene_list_;

    Scene* poped_scene_ = nullptr;
    SceneManager() = default;
};

END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// EOF
