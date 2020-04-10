///
/// @file   root_level.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_ROOT_LEVEL_HEADER_
#define INCLUDED_EGEG_ROOT_LEVEL_HEADER_

#include "level.hpp"
#include "task.hpp"

class RootLevel :
    public EGEG Level
{
public :
    RootLevel( EGEG LevelManager* Manager ) :
        Level( Manager )
    {}

    bool initialize() override;
    void finalize() override;

    void update( uint64_t DeltaTime );

private :
    EGEG Task task_;
};

REGISTER_TOP_LEVEL( RootLevel );

#endif /// !INCLUDED_EGEG_ROOT_LEVEL_HEADER_
/// EOF
