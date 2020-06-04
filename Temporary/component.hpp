#pragma once
#include "level_node.hpp"

class Component
{
public :
    Component( LevelNode* Owner ) noexcept :
        owner_{ Owner }
    {
    }
    virtual ~Component() = default;

    virtual bool initialize() = 0;
    virtual void finalize() = 0;
    LevelNode* getOwner() { return owner_; }
private :
    LevelNode* owner_;
};
