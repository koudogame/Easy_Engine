///
/// @file   
/// @author ��
///
#ifndef INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
#define INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_

#include <memory>
#include "rendering_engine.hpp"
#include "noncopyable.hpp"

BEGIN_EGEG

///
/// @class   RenderingEngineChild
/// @brief   �����_�����O�G���W���ɐ��������I�u�W�F�N�g
/// @details �G���W���ɂ�萶������邱�Ƃ�O��Ƃ��Ă��܂��B
///
class RenderingEngineChild :
    NonCopyable<RenderingEngineChild>
{
public :
    virtual ~RenderingEngineChild() {}

    void setRenderingEngine( RenderingEngine* Ptr )
    {
        if( Ptr ) engine_ = Ptr;
    }

protected :
    RenderingEngine* engine_;
};

END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
/// EOF
