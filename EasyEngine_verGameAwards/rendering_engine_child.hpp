///
/// @file   
/// @author 板場
///
#ifndef INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_
#define INCLUDED_EG_EG_RENDERING_ENGINE_CHILD_HEADER_

#include "rendering_engine.hpp"
#include "noncopyable.hpp"

BEGIN_EGEG

///
/// @class   RenderingEngineChild
/// @brief   レンダリングエンジンに生成されるオブジェクト
/// @details エンジンにより生成されることを前提としているので、コピーを禁止しています。
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
