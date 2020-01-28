///
/// @file   scene.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  Scene
///
/// @brief  �V�[�����N���X
///
class Scene
{
public :
    virtual ~Scene() = default;

    void setActive( bool State ) { is_active_ = State; }
    bool isActive() const { return is_active_; }

private :
    bool is_active_ = false;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
