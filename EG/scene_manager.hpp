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
// �V���O���g���N���X�B�C���X�^���X�ւ̃A�N�Z�X�� instance�֐����g�p���Ă��������B
// �V�[���̈����� stack(������o��) �ł��B 
// �A�N�e�B�u�ȃV�[���͍Ō�ɒǉ����ꂽ�V�[�����w���܂��B
// update�֐� �y�� draw�֐� �̓��X�g�ɕۑ����Ă���S�ẴV�[���ɑ΂��Ċ֐��̌Ăяo�����s���܂��B
//
class SceneManager
{
public :
    // �C���X�^���X�ւ̃A�h���X���擾���܂��B
    static SceneManager* instance() { static SceneManager i; return &i; }

    //
    // �A�N�e�B�u�ȃV�[����update�֐����Ăяo���܂��B
    //
    void update();
    //
    // �A�N�e�B�u�ȃV�[����draw�֐����Ăяo���܂��B
    //
    void draw();

    //
    // �A�N�e�B�u�ȃV�[�����擾���܂��B
    //
    inline Scene* getActive() const { return scenes_.back(); }
    //
    // �V�[����ǉ����܂��B
    // ���̎��ǉ������ʒu�� ��ԍŌ�ł��B
    // 
    // in Next : �ǉ�����V�[��
    //
    inline void push( Scene* Next ) { scenes_.push_back( Next ); }
    //
    // �V�[�������O���܂��B
    // ���̎����O�̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���ł��B
    //
    void pop();
    //
    // �V�[�������ւ��܂��B
    // ���̎�����ւ��̑ΏۂƂȂ�V�[���� �Ō�ɒǉ����ꂽ�V�[���ł��B
    //
    // in Next : ����ւ���̃V�[��
    //
    void swap( Scene* Next );

private :
    std::vector<Scene*> scenes_;

    Scene* poped_scene_ = nullptr;
    SceneManager() = default;
};
END_EG_EG
#endif // INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
// EOF
