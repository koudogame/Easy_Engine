///
/// @file   component3d.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_COMPONENT3D_HEADER_
#define INCLUDED_EGEG_COMPONENT3D_HEADER_

#include "component.hpp"
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class Component3D
/// @brief 3D�A�N�^�[�p�R���|�[�l���g
///
class Component3D :
    public Component
{
public :
    Component3D( Actor3D* Owner ) :
        Component{ Owner }
    {}

    ///
    /// @brief  �I�[�i�[�̎擾( overload )
    ///
    /// @return �I�[�i�[
    ///
    /// @details �I�[�i�[��Actor3D����h�����Ă��邱�Ƃ��m�肵�Ă���̂� <br>
    ///           �߂�l�̌^��Actor3D*
    ///
    Actor3D* getOwner() const noexcept { return static_cast<Actor3D*>(getOwner()); }
};

END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT3D_HEADER_
/// EOF
