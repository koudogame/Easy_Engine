#pragma once
#include "level_node.hpp"

class LevelEntity :
    public LevelNode
{
public :
    enum class EntityType
    {
        kActor,
        kCamera,
        kLight
    };

    static constexpr NodeType kNodeType = NodeType::kEntity;

    virtual EntityType getEntityType() const noexcept = 0;

// override
    NodeType getNodeType() const noexcept { return kNodeType; }
};
