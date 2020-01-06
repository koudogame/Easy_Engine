// 作成者 : 板場
#include "rendering_manager.hpp"

#include "renderer_d3d11.hpp"

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// コンストラクタ
RenderingManager::RenderingManager()
{
    renderer_ = RendererD3D11::create();
}
// デストラクタ
RenderingManager::~RenderingManager()
{
    delete renderer_;
}
END_EG_EG
// EOF
