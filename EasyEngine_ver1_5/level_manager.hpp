///
/// @file   level_manager.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
#define INCLUDED_EGEG_LEVEL_MANAGER_HEADER_

#include <vector>
#include <memory>
#include <string>
#include "non_copyable.hpp"
#include "level.hpp"
#include "task.hpp"

BEGIN_EGEG

///
/// @class  LevelManager
/// @brief  レベルマネージャ―
///
class LevelManager final :
    NonCopyable<LevelManager>
{
public :
    static std::unique_ptr<LevelManager> create();
    ~LevelManager() = default;

    void switching( std::string LevelFile );
    void replace( std::string LevelFile );
    void push( std::string& LevelFile );
    void back();

    void deferredUnload( uint64_t );
private :
    LevelManager() noexcept;
    std::unique_ptr<Level> createLevel( const std::string& );

    Task task_;
    std::vector<std::unique_ptr<Level>> levels_;
    size_t path_index_ = 0U;
    std::vector<std::string> transition_path_;
    std::vector<std::unique_ptr<Level>> reserved_unload_levels_;
    std::vector<std::unique_ptr<Level>> unloaded_levels_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_MANAGER_HEADER_
/// EOF
