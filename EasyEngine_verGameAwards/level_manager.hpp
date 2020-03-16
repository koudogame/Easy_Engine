///
/// @file   level_manager.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#include <vector>
#include "egeg.hpp"
BEGIN_EGEG
class Level;    ///< Levelクラス前方前言( 循環参照回避 )

///
/// @class  LevelManager
/// @brief  レベルマネージャー
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
