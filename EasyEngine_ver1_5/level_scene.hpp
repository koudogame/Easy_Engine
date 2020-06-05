///
/// @file   level_scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_LEVEL_SCENE_HEADER_
#define INCLUDED_EGEG_LEVEL_SCENE_HEADER_

#include "level_node.hpp"

BEGIN_EGEG

///
/// @class  LevelScene
/// @brief  ���x���m�[�h�u�V�[���v
///
/// @details �`���Ԃł��B
///
class LevelScene :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kScene;
    NodeType getNodeType() const noexcept { return kNodeType; }

    virtual void begin() = 0;
    // TODO : virtual void render(...) = 0;
    virtual void end() = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_SCENE_HEADER_
/// EOF
