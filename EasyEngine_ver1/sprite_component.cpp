// 作成者 : 板場
#include "sprite_component.hpp"
#include "render_batch.hpp"
#include "rendering_manager.hpp"
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

    // 頂点座標の設定
    const float kLeft = 0.0F;
    const float kTop  = 0.0F;
    const float kRight = static_cast<float>(pTexture->getWidth());
    const float kBottom = static_cast<float>(pTexture->getHeight());
    Mesh& mesh = sprite_.mesh;
    mesh.vertices[0].position = Vector3D{ kLeft, kTop, Depth };       // 左上
    mesh.vertices[1].position = Vector3D{ kRight, kTop, Depth };      // 右上
    mesh.vertices[2].position = Vector3D{ kLeft, kBottom, Depth };    // 左下
    mesh.vertices[3].position = Vector3D{ kRight, kBottom, Depth };   // 右下

    // 頂点座標の変換
    const Matrix3x3 kTranslation   = Matrix3x3::createTranslationMatrix( Position );
    const Matrix3x3 kRotarion      = Matrix3x3::createRotationMatrix( RotationDEG );
    const Matrix3x3 kScaling       = Matrix3x3::createScalingMatrix( Scale );
    const Matrix3x3 kRevOrigin     = Matrix3x3::createTranslationMatrix( Origin * -1.0F );
    const Matrix3x3 kTransform     = kTranslation * kRotarion * kScaling * kRevOrigin;
    for( auto& vertex : mesh.vertices )
    {
        vertex.position = kTransform * vertex.position;
    }

    // 頂点座標の正規化
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kXCoefficient = (0.5F / kScreenSize.x );
    const float kYCoefficient = -(0.5F / kScreenSize.y );
    for( auto& vertex : mesh.vertices )
    {
        vertex.position.x = (vertex.position.x * kXCoefficient) - 1.0F;
        vertex.position.y = (vertex.position.y * kYCoefficient) - 1.0F;
    }

    // UV座標の設定
    const float kRecWidth  = 1.0F / pTexture->getWidth();
    const float kRecHeight = 1.0F / pTexture->getHeight();
    const float kUVLeft   = Trimming.x * kRecWidth;
    const float kUVRight  = Trimming.z * kRecWidth;
    const float kUVTop    = Trimming.y * kRecHeight;
    const float kUVBottom = Trimming.w * kRecHeight;
    mesh.vertices[0].uv = { kUVLeft, kUVTop };
    mesh.vertices[1].uv = { kUVRight, kUVTop };
    mesh.vertices[2].uv = { kUVLeft, kUVBottom };
    mesh.vertices[3].uv = { kUVRight, kUVBottom };

    // 頂点カラーのセット
    for( auto& vertex : mesh.vertices )
    {
        vertex.color_rgba = { Color.x, Color.y, Color.z, Alpha };
    }

    visible_ = true;
    validity_ = true;
}

// 描画
void SpriteComponent::render()
{
    if( validity_ && visible_ )
    {
        RenderingManager::instance()->render( sprite_ );
    }
}

// 初期化処理
bool SpriteComponent::initialize()
{
    validity_ = false;
    visible_ = false;
    sprite_.mesh.vertices.reserve( 4U );
    sprite_.mesh.indices.reserve( 2U );
    sprite_.mesh.indices[0] = { 0, 1, 2 };
    sprite_.mesh.indices[1] = { 1, 3, 2 };

    // シェーダーのロード
    if( ShaderManager::instance()->loadVertexShader(::kSpriteVertexShaderPath, &sprite_.vertex_shader) == false )
        return false;
    if( ShaderManager::instance()->loadPixelShader(::kSpritePixelShaderPath, &sprite_.pixel_shader) == false )
        return false;
    sprite_.geometry_shader = nullptr;

    // 初期値の設定
    sprite_.texture = nullptr;

    // コンポーネントの登録
    RenderBatch::instance()->registerComponent( this );

    validity_ = true;
    return true;
}

// 終了処理
void SpriteComponent::finalize()
{
    // テクスチャの開放
    if( sprite_.texture ) { sprite_.texture->release(); }

    // コンポーネントの登録解除
    RenderBatch::instance()->unregisterComponent( this );

    // シェーダーのアンロード
    ShaderManager::instance()->unloadPixelShader( &sprite_.pixel_shader );
    ShaderManager::instance()->unloadVertexShader( &sprite_.vertex_shader );

}
END_EGEG
// EOF
