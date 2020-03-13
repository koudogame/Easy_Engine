///
/// @file   rendering_engine_child.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING_ENGINE_CHILD_HEADER_
#define INCLUDED_EGEG_RENDERING_ENGINE_CHILD_HEADER_
#include "rendering_engine.hpp"
BEGIN_EGEG
///
/// @class  RenderingEngineChild
/// @brief  レンダリングエンジンによって生成されたクラス
///
class RenderingEngineChild
{
public :
    std::shared_ptr<RenderingEngine> getEngine() const noexcept { return engine_; }

protected :
    virtual ~RenderingEngineChild() = default;
    RenderingEngineChild( const std::shared_ptr<RenderingEngine>& Engine ) :
        engine_( Engine )
    {}
    std::shared_ptr<RenderingEngine> engine_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_ENGINE_CHILD_HEADER_
/// EOF
