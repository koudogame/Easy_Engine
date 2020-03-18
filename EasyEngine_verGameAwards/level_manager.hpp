///
/// @file   level_manager.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#include <memory>
#include <vector>
#include "factory.hpp"
BEGIN_EGEG
class Level;    ///< Level�N���X�O���O��( �z�Q�Ɖ�� )
using LevelFactory = Factory<Level>;

///
/// @class  LevelManager
/// @brief  ���x���}�l�[�W���[
///
class LevelManager
{
public :

    ///
    /// @brief   ���x���̑J��
    /// @details ���݂̃��x����j�����A�J�ڂ̗�����ێ����܂��B
    ///
    /// @tparam NewLevel : �J�ڐ惌�x���^
    ///
    template <class NewLevel>
    void transition()
    {

    }

    ///
    /// @brief   ���x���̑J��
    /// @details ���݂̃��x���͔j�������A�J�ڂ̗�����ێ����܂��B
    ///
    /// @tparam NewLevel : �J�ڐ惌�x���^
    ///
    template <class NewLevel>
    void push();

    ///
    /// @brief   ���x���̑J��
    /// @details ���݂̃��x����j�����A�@�ۂ̗�����ێ����܂���B
    ///
    /// @tparam NewLevel : �J�ڐ惌�x���^
    ///
    template <class NewLevel>
    void swap();

    ///
    /// @brief   ���x���̑J��
    /// @details �������Q�Ƃ��A��O�̃��x���֑J�ڂ��܂��B<br>
    ///          �J�ڐ�̃��x�����Ȃ��ꍇ�A�@�ۂ��s���܂���B<br>
    ///          �J�ڐ�̃��x���Ɋւ��āA�C���X�^���X���c���Ă���ꍇ�V�������x���̐����͍s���܂���B
    ///
    void back();

private :
    std::vector<std::unique_ptr<Level>> level_list_;
    std::vector<uint32_t> transition_path_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
