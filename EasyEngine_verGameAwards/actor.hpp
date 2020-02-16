///
/// @file   actor.hpp
/// @author ��
///
#ifndef INCLUDED_ACTOR_HEADER_
#define INCLUDED_ACTOR_HEADER_
#include <cstdint>
#include "game_unit.hpp"
BEGIN_EGEG
///
/// @class  Actor
/// @brief  �A�N�^�[���
///
class Actor :
    public GameUnit
{
public :
    Actor( uint32_t ActorID ) noexcept : id_( ActorID ) {}

    uint32_t getID() const noexcept { return id_; }

private :
    uint32_t id_;   /// �A�N�^�[����ID
};
END_EGEG
#endif /// INCLUDED_ACTOR_HEADER_
/// EOF
