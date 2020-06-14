///
/// @file   level_empty.hpp
/// @author î¬èÍ
///
#ifndef INCLUDED_EGEG_LEVEL_EMPTY_HEADER_
#define INCLUDED_EGEG_LEVEL_EMPTY_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  LevelEmpty
/// @brief  ãÛÉmÅ[Éh
///
class LevelEmpty :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kEmpty;
    NodeType getNodeType() const noexcept override { return kNodeType; }

    bool initialize( std::istream& ) override { return true; }
    void finalize() override {}
};

REGISTER_LEVEL_NODE( LevelEmpty, Empty );

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_EMPTY_HEADER_
/// EOF
