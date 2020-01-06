#ifndef INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
// 作成者 : 板場
#include "renderer.hpp"

BEGIN_EG_EG
//
// レンダラーの管理を行う。
// シングルトンクラスです。インスタンスへのアクセスには instance関数を使用して下さい。
//
class RenderingManager
{
public :
    ~RenderingManager();

    static RenderingManager* instance() { static RenderingManager i; return &i; }

    IRenderer* getRenderer() const { return renderer_; }

private :
    RenderingManager();

    IRenderer* renderer_ = nullptr;
};
END_EG_EG
#endif // INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
// EOF
