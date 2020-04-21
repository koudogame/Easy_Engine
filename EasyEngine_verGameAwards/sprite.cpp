// 作成者 : 板場
#include "sprite.hpp"
#include "easy_engine.hpp"
#include "shader_loader.hpp"

namespace
{
    long kTextureWidth = 1280L;
    long kTextureHeight = 720L;
}

USING_NS_EGEG;

// 初期化
bool Sprite::initialize()
{
    // 描画コンポーネントの設定
    auto render = addComponent<component::Rendering2D>();
    if( !render ) return false;
     // シェーダーのロードとセット
    auto shader_loader = EasyEngine::getRenderingManager()->getShaderLoader();
    vertex_shader_ = std::move(shader_loader->loadVertexShader<SpriteVertexShader>().get());
    if( !vertex_shader_ ) return false;
    pixel_shader_ = std::move(shader_loader->loadPixelShader<SpritePixelShader>().get());
    if( !pixel_shader_ ) return false;
    render->setVertexShader( vertex_shader_.get() );
    render->setPixelShader( pixel_shader_.get() );

    return true;
}

// 終了
void Sprite::finalize()
{

}
// EOF
