///
/// @file   level_actor.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_ACTOR_HEADER_
#define INCLUDED_EGEG_LEVEL_ACTOR_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  LevelActor
/// @brief  レベルノード「アクター」
///
/// @details アクターです。ゲームに出てくるキャラクター等はこのクラスを継承してください。
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
