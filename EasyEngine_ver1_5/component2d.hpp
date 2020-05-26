///
/// @file   component2d.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_COMPONENT2D_HEADER_
#define INCLUDED_EGEG_COMPONENT2D_HEADER_

#include "component.hpp"
#include "actor2d.hpp"

BEGIN_EGEG

///
/// @class Component2D
/// @brief 2D�A�N�^�[�p�R���|�[�l���g
///
class Component2D :
    public Component
{
public :
    Component2D( Actor2D* Owner ) :
        Component{ Owner }
    {}

    ///
    /// @brief �I�[�i�[�̎擾( overload )
    ///
    /// @return �I�[�i�[
    ///
    /// @details �I�[�i�[��Actor2D����h�����Ă��邱�Ƃ��m�肵�Ă���̂� <br>
    ///           �߂�l�̌^��Actor2D*
    ///
    Actor2D* getOwner() const noexcept { return static_cast<Actor2D*>(getOwner()); }
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT2D_HEADER_
/// EOF
