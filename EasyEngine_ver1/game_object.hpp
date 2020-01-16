///
/// @file   game_object.hpp
/// @author ��
///
/// @brief  �Q�[�����ɑ��݂���I�u�W�F�N�g�̊��N���X
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
