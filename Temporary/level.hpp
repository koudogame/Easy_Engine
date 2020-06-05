#pragma once
#include <string>
class LevelNode;

class Level
{
public :
    bool load( const std::string& );
    void unload();

    void update( uint64_t );
    void pause();
    void unpause();

    LevelNode* getRootNode() const noexcept { return root_node_; }

private :
    // タスクマネージャー
    LevelNode* root_node_;
};
 