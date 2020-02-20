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
    ///
    /// @brief  �A�N�^�[����ID�̎擾
    ///
    /// @return �A�N�^�[����ID
    ///
    uint32_t getID() const noexcept { return id_; }

protected :
    Actor( uint32_t ActorID ) noexcept : id_( ActorID ) {}

private :
    uint32_t id_;   /// �A�N�^�[����ID
};
END_EGEG
#endif /// !INCLUDED_ACTOR_HEADER_
/// EOF
