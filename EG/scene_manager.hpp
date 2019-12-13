#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_

// �쐬�� : ��

#include <vector>
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
    inline Scene* getActive() const { return scenes_.back(); }
    //
    // �V�[����ǉ�����B
    // ���̎��ǉ������ʒu�� ��ԍŌ�
    // 
    // in Push : �ǉ�����V�[��
    //
    inline void push( Scene* Next ) { scenes_.push_back( Next ); }
    //
    // �V�[�������ւ���B
    // ���̎�����ւ��̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���B
    // 
    // in Next : ����ւ���̃V�[��
    //
    void swap( Scene* Next );
    //
    // �V�[�������O����B
    // ���̎����O�̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���B
    //
    void pop();

private :
    std::vector<Scene*> scenes_;

    Scene* poped_scene_ = nullptr;
    SceneManager() = default;
};

END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// EOF
