///
/// @file   
/// @author ��
///
#ifndef INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
#define INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_

#include "rendering_engine.hpp"
#include "noncopyable.hpp"

BEGIN_EGEG

///
/// @class   RenderingEngineChild
/// @brief   �����_�����O�G���W���ɐ��������I�u�W�F�N�g
/// @details �G���W���ɂ�萶������邱�Ƃ�O��Ƃ��Ă���̂ŁA�R�s�[���֎~���Ă��܂��B
///
class RenderingEngineChild :
    NonCopyable<RenderingEngineChild>
{
public :
    void setRenderingEngine( std::shared_ptr<RenderingEngine>&& Ptr )
    {
        if( Ptr ) engine_ = std::move( Ptr );
    }

    std::shared_ptr<RenderingEngine> getRenderingEngine() const noexcept { return engine_; }

protected :
    std::shared_ptr<RenderingEngine> engine_;
};

END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
/// EOF
