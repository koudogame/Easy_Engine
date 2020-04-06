///
/// @file   
/// @author ��
///
#ifndef INCLUDED_EG_EG_RENDERING_MAMAGER_CHILD_HEADER_
#define INCLUDED_EG_EG_RENDERING_MAMAGER_CHILD_HEADER_

#include <memory>
#include "rendering_manager.hpp"
#include "noncopyable.hpp"

BEGIN_EGEG

///
/// @class   RenderingManagerChild
/// @brief   �����_�����O�}�l�[�W���\�ɐ��������I�u�W�F�N�g
/// @details �G���W���ɂ�萶������邱�Ƃ�O��Ƃ��Ă��܂��B
///
class RenderingManagerChild :
    NonCopyable<RenderingManagerChild>
{
public :
    virtual ~RenderingManagerChild() {}

    void setRenderingEngine( RenderingManager* Ptr )
    {
        if( Ptr ) engine_ = Ptr;
    }

protected :
    RenderingManager* engine_;
};

END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERING_MANAGER_CHILD_HEADER_
/// EOF
