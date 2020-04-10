///
/// @file   level_manager.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_

#include <memory>
#include <vector>
#include "noncopyable.hpp"
#include "factory.hpp"      /// ���x���̓t�@�N�g���ɂ���Đ�������B
#include "type_id.hpp"      /// ���x����ID��TypeID�ɂ�萶������B
#include "constant_id.hpp"  /// �ŏ��Ɏ��s����郌�x���� ID:0 ��ݒ肷��B

///
/// @def    REGISTER_TOP_LEVEL
/// @brief  �ŏ��Ɏ��s����郌�x���̓o�^
///
/// @param[in] LevelType : �o�^���郌�x���^
///
#define REGISTER_TOP_LEVEL( LevelType ) \
REGISTER_WITH_FACTORY( EGEG LevelFactory, LevelType, EGEG ConstantID<0U> )

///
/// @def    REGISTER_LEVEL
/// @brief  ���x���̓o�^
///
/// @param[in] LevelType : �o�^���郌�x���^
///
#define REGISTER_LEVEL( LevelType ) \
REGISTER_WITH_FACTORY( EGEG LevelFactory, LevelType, EGEG LevelID<LevelType> )

BEGIN_EGEG

class Level;                                                  ///< Level�N���X�O���錾( �z�Q�Ɖ�� )
template <class LevelType> using LevelID = TypeID<LevelType>; ///< ���x���pID

///
/// @class   LevelManager
/// @brief   ���x���}�l�[�W���[
/// @details �V���O���g���N���X�ł��B
///
///
/// @details �u���݂̃��x���v�u�A�N�e�B�u�ȃ��x���v�͈�ԍŌ�ɑJ�ڂ������x���̂��Ƃ��w���܂��B<br>
///          ���x���̑J�ڂɊւ��āA���݂̃��x������̃��N�G�X�g�ł��邱�Ƃ�O��Ƃ��Ă��܂��B
///
class LevelManager final :
    NonCopyable<LevelManager>
{
public :
    ~LevelManager();
    static std::unique_ptr<LevelManager> create();

    ///
    /// @brief   ���x���̑J��
    /// @details ���ݕێ����Ă���S���x����j�����A�V�������x���𐶐����܂��B<br>
    ///           �����ɂ��郌�x���ւ̑J�ڂ̏ꍇ�A�����������܂Ŗ߂��܂��B<br>
    ///           �����ɂȂ����x���ւ̑J�ڂ̏ꍇ�A�����ɐV�������x����ǉ����܂��B
    ///
    /// @tparam NewLevelType : �J�ڐ惌�x���^
    ///
    template <class NewLevelType>
    void transition()
    {
        transition( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   ���x���̑J��
    /// @details ���݂̃��x���͔j�������A�V�������x���𐶐����܂��B<br>
    ///          �����̕ύX�͂���܂���B
    ///
    /// @tparam NewLevelType : �J�ڐ惌�x���^
    ///
    template <class NewLevelType>
    void push()
    {
        push( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   ���x���̑J��
    /// @details ���݂̃��x����j�����A�V�������x���𐶐����܂��B<br>
    ///          �J�ڗ����̍Ō�̗v�f���A�V�������x����ID�ŏ㏑�����܂��B
    ///
    /// @tparam NewLevelType : �J�ڐ惌�x���^
    ///
    template <class NewLevelType>
    void swap()
    {
        swap( LevelID<NewLevelType>() );
    }

    ///
    /// @brief   ���x���̑J�� 
    /// @details ���݂̃��x����j��������A�J�ڗ������Q�Ƃ���O�̃��x���֑J�ڂ��܂��B<br>
    ///          �J�ڐ�̃��x�����Ȃ��ꍇ�A�J�ڂ��s���܂���B<br>
    ///          �J�ڐ�̃��x���Ɋւ��āA�C���X�^���X���c���Ă���ꍇ�V�������x���̐����͍s���܂���B
    ///
    void back();

private :
    LevelManager();

    std::unique_ptr<Level> createLevel( uint32_t LevelID );
    void transition( uint32_t );
    void push( uint32_t );
    void swap( uint32_t );

    std::vector<std::unique_ptr<Level>> level_list_;
    size_t path_idx_ = 0U;
    std::vector<uint32_t> transition_path_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
