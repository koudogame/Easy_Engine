///
/// @file   level_manager.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_

#include <memory>
#include <string>
#include "non_copyable.hpp"
#include "task.hpp"

BEGIN_EGEG

class Level;    ///< Level�O���錾( �z�Q�Ɖ�� )

///
/// @class LevelManager
/// @brief ���x���}�l�[�W���[
///
class LevelManager final :
    NonCopyable<LevelManager>
{
public :
    static std::unique_ptr<LevelManager> create();
    ~LevelManager();

    ///
    /// @brief   ���x���̑J��
    ///
    /// @param[in] LevelFilePath : �ǂݍ��ރ��x���\���t�@�C���̃p�X
    ///
    /// @details ���ݕێ����Ă���S���x����j�����A�V�������x���𐶐����܂��B <br>
    ///           �����ɂ��郌�x���ւ̑J�ڂ̏ꍇ�A�����������܂Ŗ߂��܂��B <br>
    ///           �����ɂȂ����x���ւ̑J�ڂ̏ꍇ�A�����ɐV�������x����ǉ����܂��B
    ///
    void transition( std::string LevelFilePath );

    ///
    /// @brief   ���x���̒ǉ�
    ///
    /// @param[in] LevelFilePath : �ǂݍ��ރ��x���\���t�@�C���̃p�X
    ///
    /// @details ���݂̃��x����j�������A�V�������x����ǉ����܂��B <br>
    ///           �J�ڗ����̕ύX�͂���܂���B
    ///
    void push( const std::string& LevelFilePath );

    ///
    /// @brief   ���݂̃��x�������ւ���
    ///
    /// @paramp[in] LevelFilePath : �ǂݍ��ރ��x���\���t�@�C���̃p�X
    ///
    /// @details ���݂̃��x����j�����A�V�������x���Ɠ���ւ��܂��B <br>
    ///           �J�ڗ����̍Ō�̗v�f��V�������x���ŏ㏑�����܂��B
    ///
    void swap( std::string LevelFilePath );

    ///
    /// @brief   1�O�̃��x���֖߂�
    ///
    /// @details ���݂̃��x����j��������A�J�ڗ������Q�Ƃ���1�O�̃��x���֑J�ڂ��܂��B <br>
    ///           1�O�̃��x�����Ȃ��ꍇ�A�J�ڂ͍s���܂���B <br>
    ///           1�O�̃��x���ɂ��āApush()�ɂ��J�ڂ̌�ŃC���X�^���X���c���Ă���ꍇ�͐V�������x���̐������s���܂���B
    ///
    void back();



    void destructionFinalizedLevel( uint64_t );
private :
    LevelManager() noexcept;
    std::unique_ptr<Level> createLevel( const std::string& );

    Task task_;
    std::vector<std::unique_ptr<Level>> levels_;
    size_t path_index_ = 0U;
    std::vector<std::string> transition_path_;
    std::vector<std::unique_ptr<Level>> finalized_levels_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
