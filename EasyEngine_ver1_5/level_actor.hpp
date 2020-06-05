///
/// @file   level_actor.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_ACTOR_HEADER_
#define INCLUDED_EGEG_LEVEL_ACTOR_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  LevelActor
/// @brief  ���x���m�[�h�u�A�N�^�[�v
///
/// @details �A�N�^�[�ł��B�Q�[���ɏo�Ă���L�����N�^�[���͂��̃N���X���p�����Ă��������B
///
class LevelActor :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kActor;
    NodeType getNodeType() const noexcept { return kNodeType; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_ACTOR_HEADER_
/// EOF
