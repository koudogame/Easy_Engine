///
/// @file   game_object.hpp
/// @author 板場
///
/// @brief  ゲーム中に存在するオブジェクトの基底クラス
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#include <unordered_map>
#include "component.hpp"
BEGIN_EGEG
class GameObject
{
public :


private :
    std::unordered_map<uint16_t, Component*> components_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
