///
/// @file   level_manager.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#include <vector>
#include "egeg.hpp"
BEGIN_EGEG
class Level;    ///< Level�N���X�O���O��( �z�Q�Ɖ�� )

///
/// @class  LevelManager
/// @brief  ���x���}�l�[�W���[
///
class LevelManager
{
public :


private :
    std::vector<Level*> level_list_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
