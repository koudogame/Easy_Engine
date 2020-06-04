#pragma once
#include <string>
class LevelNode;

class Level
{
public :
    bool load( const std::string& );
    void unload();

    LevelNode* getRootNode() const noexcept { return root_node_; }

private :
    // �^�X�N�}�l�[�W���[
    LevelNode* root_node_;
};
