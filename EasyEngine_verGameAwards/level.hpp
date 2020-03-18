///
/// @file   level.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_HEADER_
#define INCLUDED_EGEG_LEVEL_HEADER_
#include "level_manager.hpp"
BEGIN_EGEG
///
/// @file   Level
/// @brief  ���x�����
///
class Level
{
public :
    ///
    /// @breif  �R���X�g���N�^
    ///
    /// @param[in] Manager : ���x���}�l�[�W���[
    ///
    Level( LevelManager* Manager ) :
        manager_( Manager )
    {}

    ///
    /// @brief  ����������
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @breif  �I������
    ///
    virtual void finalize() = 0;

    ///< ���x���}�l�[�W���[�̎擾
    LevelManager* getManager() const noexcept { return manager_; }

private :
    LevelManager* manager_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_HEADER_
/// EOF
