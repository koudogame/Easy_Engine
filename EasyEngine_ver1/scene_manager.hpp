///
/// @file    scene_manager.hpp
/// @author  ��
///
#ifndef INCLUDED_EGEG_SCENE_MANAGER_HEADER_
#define INCLUDED_EGEG_SCENE_MANAGER_HEADER_
#include <deque>
#include "scene.hpp"
BEGIN_EGEG
///
/// @class  SceneManager
///
/// @brief   �V�[���}�l�[�W���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B<br>
///          �V�[���̓X�^�b�N�Ǘ��ł��B�ł��Ō�ɒǉ����ꂽ�V�[�����A�N�e�B�u�Ƃ��܂��B<br>
///          pop,swap�֐��͓����ŃA�N�e�B�u�V�[���̊J�����s���Ă��܂��B<br>
///          ���̊֐��̌Ăяo����A�A�N�e�B�u�V�[���̂��w���|�C���^�̓_���O�����O�|�C���^�ɂȂ�܂��B
///
class SceneManager
{
public :
    ~SceneManager();

    ///
    /// @brief  �C���X�^���X�̎擾
    ///
    /// @return �C���X�^���X
    ///
    static SceneManager* instance() { static SceneManager i; return &i; }

    ///
    /// @brief   �V�[����ǉ�����
    /// @details �V�[���̃��[�h�����s����܂��B
    ///
    /// @param[in] SceneID : �ǉ�����V�[����ID
    ///
    void push( uint32_t SceneID );
    ///
    /// @brief   �Ō�ɒǉ����ꂽ�V�[�����폜����
    /// @details �V�[�����������݂���ꍇ�̂ݗL���ł��B
    ///
    void pop();
    ///
    /// @brief   �V�[�������ւ���
    /// @details �V�[���̃��[�h�����s����܂��B
    ///
    /// @param[in] SceneID : ����ւ���̃V�[��ID
    ///
    void swap( uint32_t SceneID );

private :
    SceneManager();
    SceneManager( const SceneManager& ) = delete;
    SceneManager& operator=( const SceneManager& ) = delete;

    std::deque<Scene*> scenes_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_MANAGER_HEADER_
/// EOF
