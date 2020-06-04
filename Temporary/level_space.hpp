#pragma once
#include "level_node.hpp"

class LevelSpace :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kSpace;


private :
    // 衝突コンポーネントのリスト
};
