///
/// @file   
/// @author 板場
///
#ifndef INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
#define INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_

#include <memory>
#include "rendering_engine.hpp"
#include "noncopyable.hpp"

BEGIN_EGEG

///
/// @class   RenderingEngineChild
/// @brief   レンダリングエンジンに生成されるオブジェクト
/// @details エンジンにより生成されることを前提としています。
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
