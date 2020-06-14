///
/// @file   level.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include "task.hpp"
#include "level_empty.hpp"

BEGIN_EGEG

///
/// @class  Level
/// @brief  ���x��
///
/// @detailes  ���x���̓c���[�\���̃��x���m�[�h�ɂ��\������܂��B           <br>
///                                                                    <br>
///            ���[�g�m�[�h�̒��ڂ̎q�ɓ�����W���ɁA�x�[�X�V�[���͈ʒu���܂��B <br>
///            �x�[�X�V�[���͕K���A���̃V�[��������ɔz�u���ĉ������B        <br>
///            ���̗v���ɂ��A�x�[�X�V�[���ւ̃A�N�Z�X����ӂȂ��̂ɂł��܂��B <br>
///            �x�[�X�V�[���փA�N�Z�X )                                   <br>
///             Level level;                                           <br>
///                 ...level��������...                                 <br>
///             LevelNode* root_node = level->getRootNode();           <br>
///             LevelScene* base_scene = root_node->getChild<LevelScene>( 0 );
///
class Level
{
public :
    ///
    /// @brief  ���x���t�@�C�������[�h
    ///
    /// @return true:�����@false:���s
    ///
    bool load( const std::string& LevelFilePath );
    ///
    /// @brief  ���x�����A�����[�h
    ///
    void unload();

    ///
    /// @brief  �|�[�Y( �X�V�ꎞ��~ )
    ///
    /// @details �`��͎~�܂�܂���B <br>
    ///          �`����~�߂����ꍇ�A�x�[�X�V�[���̕`��R���|�[�l���g�̕`��X�e�[�g��ύX���Ă��������B
    ///
    void pause();
    ///
    /// @brief  �|�[�Y����( �ꎞ��~���� )
    ///
    void unpause();

    ///
    /// @brief  �^�X�N�}�l�[�W���[���擾
    ///
    TaskManager* getTaskManager() noexcept { return &task_manager_; }

    ///
    /// @brief  ���[�g�m�[�h���擾
    ///
    LevelNode* getRootNode() const noexcept { return root_node_.get(); }

private :
    bool loadNodes( std::istream& );
    std::unique_ptr<LevelNode> loadNode( std::string&, std::istream& );

    Task task_update_;
    Task task_render_;
    TaskManager task_manager_;
    std::unique_ptr<LevelNode> root_node_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
