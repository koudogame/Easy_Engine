// 作成者 : 板場
#include "sprite_component.hpp"
#include "render_batch.hpp"
#include "system_manager.hpp"
#include "rendering_manager.hpp"
#include "texture_manager.hpp"
#include "shader_manager.hpp"

namespace
{
    enum VertexPosition
    {
        kTopLeft,
        kTopRight,
        kBottomLeft,
        kBottomRight
    };

    constexpr char kVertexShaderPath[] = "sprite_vs.cso";  // コンパイル済み 頂点シェーダーファイルパス
    constexpr char kPixelShaderPath[] = "sprite_ps.cso";   // コンパイル済み ピクセルシェーダ―ファイルパス
} // !unnamed namespace


BEGIN_EGEG
// SpriteComponent : public 関数の実装
/*===========================================================================*/
// コンストラクタ
SpriteComponent::SpriteComponent( Actor* Owner ) :
    RenderComponent( Owner ),
    is_validity_( false )   // 初期化処理が呼び出される前に描画されることを防ぐ
{
}   

#if true
// スプライト情報のセット
void SpriteComponent::setStatus( 
    ITexture* pTexture, 
    const Vector2D& Position, 
    const Vector4D& Trimming,
    float AngleDEG, 
    const Vector2D& Scale, 
    const Vector2D& Origin, 
    const Vector3D& Color,
    float Alpha, 
    float Depth )
{
    setTexture( pTexture );
    setPosition( Position );
    setTrimming( Trimming );
    setScale( Scale );
    setOrigin( Origin );
    setColor( Color );
    setAlpha( Alpha );
    setDepth( Depth );
}

// テクスチャのセット
void SpriteComponent::setTexture( ITexture* pTexture )
{
    pTexture->addRef();

    // 既にあるテクスチャを解放する
    if( p_texture_ ) TextureManager::instance()->unload( &p_texture_ );

    p_texture_ = pTexture;
}

// 初期化処理
bool SpriteComponent::initialize()
{
    // シェーダーの読み込み
    if( ShaderManager::instance()->loadVertexShader(::kVertexShaderPath, &p_vertex_shader_) == false )
    {
        std::string err = "シェーダーファイルの読み込みに失敗しました。\n";
        err += "ファイル : ";
        err += ::kVertexShaderPath;
        err += "\n\n場所 : SpriteComponent::initialize";

        SystemManager::instance()->showDialogBox( err );
        return false;
    }
    if( ShaderManager::instance()->loadPixelShader(::kPixelShaderPath, &p_pixel_shader_) == false )
    {
        std::string err = "シェーダーファイルの読み込みに失敗しました。\n";
        err += "ファイル : ";
        err += ::kPixelShaderPath;
        err += "\n\n場所 : SpriteComponent::initialize";

        SystemManager::instance()->showDialogBox( err );
        return false;
    }


    // 正常終了
    is_visible_ = true;
    is_validity_ = true;
    return true;
}

// 終了処理
void SpriteComponent::finalize()
{
    ShaderManager::instance()->unloadVertexShader( &p_vertex_shader_ );
    ShaderManager::instance()->unloadPixelShader( &p_pixel_shader_ );
}

// 描画処理
void SpriteComponent::render()
{
    if( is_validity_ == false || is_visible_ == false ) 
        return;

    // モデルを描画
    Model sprite;
    sprite.mesh.vertices.reserve( 4U ); // 4頂点
    sprite.mesh.indices.reserve( 2U );  // 2ポリゴン
    getModelStatus( &sprite );
    RenderingManager::instance()->renderModel( sprite );
}

// SpriteComponent : private 関数の実装
/*===========================================================================*/
// モデルの状態を取得
// この関数呼び出した時点での、スプライト情報からモデルの状態を決定します。
//
// out pModel : 状態を取得するモデルのアドレス
void SpriteComponent::getModelStatus( Model* pModel )
{
    // 頂点データの設定
    Vector3D position[4];
    getVerticesPositoin( position );
    Vector2D uv[4];
    getVerticesUV( uv );
    for( int i = 0; i < 4; ++i )
    {
        pModel->mesh.vertices.push_back(
            { /*position[i],*/ uv[i], color_ }
        );
    }
    
    // 頂点インデックスの設定
    pModel->mesh.indices.push_back( { ::kTopLeft, ::kTopRight, ::kBottomLeft } );
    pModel->mesh.indices.push_back( { ::kTopRight, ::kBottomRight, ::kBottomLeft } );

    // テクスチャの設定
    pModel->texture = p_texture_;

    // シェーダーの設定
    pModel->vertex_shader = p_vertex_shader_;
    pModel->geometry_shader = nullptr;
    pModel->pixel_shader = p_pixel_shader_;
}

// 頂点座標を取得
//
// out arrPosition[4] : 状態を取得する配列
void SpriteComponent::getVerticesPositoin( Vector3D arrPosition[4] )
{
    // 切り取り範囲から大きさを算出
    const float kLeft   = 0.F;
    const float kTop    = 0.F;
    const float kRight  = trimming_.z - trimming_.x;
    const float kBottom = trimming_.w - trimming_.y;
    arrPosition[::kTopLeft]     = { kLeft,  kTop, 1.F };
    arrPosition[::kTopRight]    = { kRight, kTop, 1.F };
    arrPosition[::kBottomLeft]  = { kLeft,  kBottom, 1.F };
    arrPosition[::kBottomRight] = { kRight, kBottom, 1.F };

    // 変換行列の作成
    const Matrix3x3 kTranslation = Matrix3x3::createTranslationMatrix( position_ );
    const Matrix3x3 kRotation    = Matrix3x3::createRotationMatrix( rotation_ );
    const Matrix3x3 kScaling     = Matrix3x3::createScalingMatrix( scale_ );
    const Matrix3x3 kRevOrigin   = Matrix3x3::createTranslationMatrix( origin_ * -1.F );
    const Matrix3x3 kTransform = kTranslation * kRotation * kScaling * kRevOrigin;
 
    // 座標の変換＆正規化
    const Vector2D kScreenSize = RenderingManager::instance()->getScreenSize();
    const float kCoefficientX = 2.F / kScreenSize.x;
    const float kCoefficientY = -2.0F / kScreenSize.y;
    for( int i = 0; i < 4; ++i )
    {
        arrPosition[i] = kTransform * arrPosition[i];
        arrPosition[i].x = arrPosition[i].x * kCoefficientX - 1.F;
        arrPosition[i].y = arrPosition[i].y * kCoefficientY + 1.F;
    }
}

// 頂点UV座標を取得
//
//out arrUV[4] : 状態を取得する配列
void SpriteComponent::getVerticesUV( Vector2D arrUV[4] )
{
    const float kRecWidth  = 1.F / p_texture_->getWidth();  // 割り算の数を減らすため
    const float kRecHeight = 1.F / p_texture_->getHeight(); // 割り算の数を減らすため
     
    const float kLeft   = trimming_.x * kRecWidth;
    const float kRight  = trimming_.z * kRecWidth;
    const float kTop    = trimming_.y * kRecHeight;
    const float kBottom = trimming_.w * kRecHeight;
    arrUV[::kTopLeft]     = { kLeft, kTop };
    arrUV[::kTopRight]    = { kRight, kTop };
    arrUV[::kBottomLeft]  = { kLeft, kBottom };
    arrUV[::kBottomRight] = { kRight, kBottom };
}
#else
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
    if( p_texture ) { sprite_.texture->release(); }
    sprite_.texture = pTexture;

    Vector3D vertices[4];
    const float Width  = Trimming.z - Trimming.x;
    const float Height = Trimming.w - Trimming.y;

    // 頂点座標の設定
    const float kLeft = 0.0F;
    const float kTop  = 0.0F;
    const float kRight = Width;
    const float kBottom = Height;
    vertices[0] = Vector3D{ kLeft, kTop, 1.0F };       // 左上
    vertices[1] = Vector3D{ kRight, kTop, 1.0F };      // 右上
    vertices[2] = Vector3D{ kLeft, kBottom, 1.0F };    // 左下
    vertices[3] = Vector3D{ kRight, kBottom, 1.0F };   // 右下
    // 頂点座標の変換
    const Matrix3x3 kTranslation   = Matrix3x3::createTranslationMatrix( Position );
    const Matrix3x3 kRotarion      = Matrix3x3::createRotationMatrix( RotationDEG );
    const Matrix3x3 kScaling       = Matrix3x3::createScalingMatrix( Scale );
    const Matrix3x3 kRevOrigin     = Matrix3x3::createTranslationMatrix( Origin * -1.0F );
    const Matrix3x3 kTransform     = kTranslation * kRotarion * kScaling * kRevOrigin;
    for( auto& vertex : vertices )
    {
        vertex = kTransform * vertex;
        vertex.z = Depth;
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
    const float kRecWidth  = 1.0F / pTexture->getWidth();
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
#endif
END_EGEG
// EOF
