///
/// @file   level.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_

#include "task.hpp"
#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  Level
/// @brief  ���x��
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
    /// @brief  �ǂݍ���ł���m�[�h�����
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
    LevelNode* getRootNode() const noexcept { return root_node_; }

private :
    Task task_update_;
    Task task_render_;
    TaskManager task_manager_;
    LevelNode* root_node_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
