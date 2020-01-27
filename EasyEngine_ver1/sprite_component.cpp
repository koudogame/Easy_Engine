// 作成者 : 板場
#include "sprite_component.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"
#include "texture_manager.hpp"
#include "shader_manager.hpp"

namespace
{
    constexpr char kSpriteVertexShaderPath[] = "sprite_vs.cso";  // コンパイル済み 頂点シェーダーファイルパス
    constexpr char kSpritePixelShaderPath[] = "sprite_ps.cso";   // コンパイル済み ピクセルシェーダ―ファイルパス
} // !unnamed namespace


BEGIN_EGEG
// SpriteComponent : 関数の実装
/*===========================================================================*/
// コンストラクタ
SpriteComponent::SpriteComponent()
{
}   

// スプライト情報のセット
void SpriteComponent::setStatus(
    ITexture* pTexture,
    const Vector2D& Position,
    const Vector4D& Trimming,
    float RotationDEG,
    const Vector2D& Scale,
    const Vector2D& Origin,
    const Vector3D& Color,
    float Alpha,
    float Depth )
{
    // テクスチャのセット
    pTexture->addRef();
    if( sprite_.texture ) { sprite_.texture->release(); }
    sprite_.texture = pTexture;

    Vector3D vertices[4];
    const float Width  = Trimming.z - Trimming.x;
    const float Height = Trimming.w - Trimming.y;

    // 頂点座標の設定
    const float kLeft = 0.0F;
    const float kTop  = 0.0F;
    const float kRight = Width;
    const float kBottom = Height;
    vertices[0] = Vector3D{ kLeft, kTop, Depth };       // 左上
    vertices[1] = Vector3D{ kRight, kTop, Depth };      // 右上
    vertices[2] = Vector3D{ kLeft, kBottom, Depth };    // 左下
    vertices[3] = Vector3D{ kRight, kBottom, Depth };   // 右下
    // 頂点座標の変換
    const Matrix3x3 kTranslation   = Matrix3x3::createTranslationMatrix( Position );
    const Matrix3x3 kRotarion      = Matrix3x3::createRotationMatrix( RotationDEG );
    const Matrix3x3 kScaling       = Matrix3x3::createScalingMatrix( Scale );
    const Matrix3x3 kRevOrigin     = Matrix3x3::createTranslationMatrix( Origin * -1.0F );
    const Matrix3x3 kTransform     = kTranslation * kRotarion * kScaling * kRevOrigin;
    for( auto& vertex : vertices )
    {
        vertex = kTransform * vertex;
    }
    // 頂点座標の正規化
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kXCoefficient = (2.0F / kScreenSize.x );
    const float kYCoefficient = -(2.0F / kScreenSize.y );
    for( auto& vertex : vertices )
    {
        vertex.x = (vertex.x * kXCoefficient) - 1.0F;
        vertex.y = (vertex.y * kYCoefficient) + 1.0F;
    }

    // UV座標の設定
    Float2 uv[4];
    const float kRecWidth  = 1.0 / pTexture->getWidth();
    const float kRecHeight = 1.0F / pTexture->getHeight();
    const float kUVLeft   = Trimming.x * kRecWidth;
    const float kUVRight  = Trimming.z * kRecWidth;
    const float kUVTop    = Trimming.y * kRecHeight;
    const float kUVBottom = Trimming.w * kRecHeight;
    uv[0] = { kUVLeft, kUVTop };
    uv[1] = { kUVRight, kUVTop };
    uv[2] = { kUVLeft, kUVBottom };
    uv[3] = { kUVRight, kUVBottom };

    // 頂点セット
    sprite_.mesh.vertices.clear();
    for( int i = 0; i < 4; ++i )
    {
        sprite_.mesh.vertices.push_back(
            VertexData {
                vertices[i],
                uv[i],
                { Color.x, Color.y, Color.z, Alpha }
            }
        );
    }

    visible_ = true;
    validity_ = true;
}

// 描画
void SpriteComponent::render()
{
    if( validity_ && visible_ )
    {
        RenderingManager::instance()->renderModel( sprite_ );
    }
}

// 初期化処理
bool SpriteComponent::initialize()
{
    // 初期値の設定
    validity_ = false;
    visible_ = false;
    sprite_.mesh.vertices.reserve( 4U );
    sprite_.mesh.indices.reserve( 2U );
    sprite_.mesh.indices.push_back( { 0, 1, 2 } );
    sprite_.mesh.indices.push_back( { 1, 3, 2 } );
    sprite_.texture = nullptr;

    // シェーダーの設定
    if( ShaderManager::instance()->loadVertexShader(::kSpriteVertexShaderPath, &sprite_.vertex_shader) == false )
        return false;
    if( ShaderManager::instance()->loadPixelShader(::kSpritePixelShaderPath, &sprite_.pixel_shader) == false )
        return false;
    sprite_.geometry_shader = nullptr;

    // コンポーネントの登録
    RenderBatch::instance()->registerComponent( this );

    validity_ = true;
    return true;
}

// 終了処理
void SpriteComponent::finalize()
{
    // コンポーネントの登録解除
    RenderBatch::instance()->unregisterComponent( this );

    // リソースのアンロード
    TextureManager::instance()->unload( &sprite_.texture );
    ShaderManager::instance()->unloadPixelShader( &sprite_.pixel_shader );
    ShaderManager::instance()->unloadVertexShader( &sprite_.vertex_shader );
}
END_EGEG
// EOF
