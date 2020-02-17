///
/// @file   actor.hpp
/// @author 板場
///
#ifndef INCLUDED_ACTOR_HEADER_
#define INCLUDED_ACTOR_HEADER_
#include <cstdint>
#include "game_unit.hpp"
BEGIN_EGEG
///
/// @class  Actor
/// @brief  アクター基底
///
class Actor :
    public GameUnit
{
public :
    uint32_t getID() const noexcept { return id_; }

protected :
    Actor( uint32_t ActorID ) noexcept : id_( ActorID ) {}

private :
    uint32_t id_;   /// アクター識別ID
};
END_EGEG
#endif /// INCLUDED_ACTOR_HEADER_
/// EOF
