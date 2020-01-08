///
/// @file    scene_manager.hpp
/// @author  ��
///
/// @brief   �V�[���Ǘ��N���X<br>
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          �V�[���̈�����stack(������o��)�ł��B<br>
///          �Ō�ɒǉ����ꂽ�V�[�����A�N�e�B�u�ȃV�[���Ƃ��Ĉ����܂��B
///
///
#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#include <vector>
#include "easy_engine.hpp"
BEGIN_EG_EG
class Scene;
class SceneManager
{
public :
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�ւ̃A�h���X
    ///
    static SceneManager* instance() { static SceneManager i; return &i; }

    ///
    /// @brief �ێ����Ă���V�[�����ׂĂ�updata�֐����Ăяo���܂��B
    ///
    void update();
    
    ///
    /// @brief  �ێ����Ă���V�[�����ׂĂ�draw�֐����Ăяo���܂��B
    ///
    void draw();

    ///
    /// @brief  �A�N�e�B�u�ȃV�[�����擾���܂��B
    ///
    /// @return �A�N�e�B�u�ȃV�[���ւ̃|�C���^
    ///
    inline Scene* getActive() const { return scenes_.back(); }

    ///
    /// @brief      �V�[����ǉ����܂��B
    ///
    /// @param[in]  pNext : �ǉ�����V�[���̃A�h���X
    ///
    inline void push( Scene* pNext ) { scenes_.push_back( pNext ); }

    ///
    /// @brief �V�[�������O���܂��B
    ///
    void pop();

    ///
    /// @brief �V�[�������ւ��܂��B
    ///
    /// @param[in] pNext : ����ւ���̃V�[���̃A�h���X
    ///
    void swap( Scene* pNext );

private :
    std::vector<Scene*> scenes_;    ///<    @brief �V�[�����X�g
    Scene* poped_scene_ = nullptr;  ///<    @brief ���O�����V�[�����ꎞ�i�[���Ă���

    SceneManager() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
/// EOF
