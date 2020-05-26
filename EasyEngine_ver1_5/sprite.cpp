// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "sprite.hpp"
#include "application_status.hpp"
#include "engine.hpp"
#include "table.hpp"
#include "task_order.hpp"
#include "transform2d_component.hpp"
#include "rendering_component.hpp"
#include "sprite_shader.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    const std::vector<VertexPositionType> kVertexPositions
    {
        VertexPositionType{ 0.0F, 0.0F, 0.0F },     // 左上
        VertexPositionType{ 1.0F, 0.0F, 0.0F },     // 右上
        VertexPositionType{ 0.0F, -1.0F, 0.0F },    // 左下
        VertexPositionType{ 1.0F, -1.0F, 0.0F }     // 右下
    };
    const std::vector<UINT> kVertexIndices
    {
        0, 1, 2,
        2, 1, 3
    };
}


/******************************************************************************

	Sprite

******************************************************************************/
 // 初期化
bool Sprite::initialize( std::istream& DataStream )
{
    const Table<std::string> kInitialData{ DataStream };

    if( !(shader_ = SpriteShader::create()) ) return false;
    if( !createMesh() ) return false;
    if( !loadTexture(kInitialData.get<0>()) ) return false;
    initComponent();
    registerTask();

	return true;
}


 // 終了
void Sprite::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_ );
}


 // 更新
void Sprite::update( uint64_t )
{
    // 切り取り範囲を基に、頂点のUV座標を更新する
    const float kTextureWidthReciprocal = 1.0F / texture_width_;
    const float kTextureHeightReciprocal = 1.0F / texture_height_;
    const float kTrimmingLeft   = trim_base_point_.x * kTextureWidthReciprocal;
    const float kTrimmingTop    = trim_base_point_.y * kTextureHeightReciprocal;
    const float kTrimmingRight  = (trim_base_point_.x+width_)  * kTextureWidthReciprocal;
    const float kTrimmingBottom = (trim_base_point_.y+height_) * kTextureHeightReciprocal;
    const VertexUVType kUVs[4]
    {
        VertexUVType{kTrimmingLeft, kTrimmingTop},      // 左上
        VertexUVType{kTrimmingRight, kTrimmingTop},     // 右上
        VertexUVType{kTrimmingLeft, kTrimmingBottom},   // 左下
        VertexUVType{kTrimmingRight, kTrimmingBottom}   // 右下
    };

    auto d3d_dc = EasyEngine::getRenderingManager()->getD3DDeviceContext();
    D3D11_MAPPED_SUBRESOURCE mpd{};
    auto hr = d3d_dc->Map(
        mesh_.vertices.get<TagVertexUV>().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
    if( FAILED(hr) ) return;
    memcpy( mpd.pData, kUVs, sizeof(VertexUVType)*kVertexPositions.size() );
    d3d_dc->Unmap( mesh_.vertices.get<TagVertexUV>().Get(), 0 );

}


 // ワールド変換行列を計算
DirectX::XMMATRIX Sprite::calcWorldMatrix() const
{
    using namespace DirectX;

    auto* transform = getComponent<Transform2DComponent>();
    if( !transform ) return XMMatrixIdentity();

    const auto kAdjustSizeScaling = XMMatrixScaling(width_, height_, 1.0F );
    const auto kAdjustOrigin = XMMatrixTranslation( -transform->getPivot().x, transform->getPivot().y, 0.0F );
    const auto kScaling = XMMatrixScalingFromVector( transform->getScale() );
    const auto kRotation = XMMatrixRotationZ( XMConvertToRadians(transform->getRotationDeg()) );
    const auto kTranslation = XMMatrixTranslation( transform->getPosition().x, -transform->getPosition().y, 0.0F );
    auto normalize = XMMatrixScaling(2.0F/kWindowWidth<float>, 2.0F/kWindowHeight<float>, 1.0F );
    normalize = XMMatrixMultiply( normalize, XMMatrixTranslation( -1.0F, 1.0F, 0.0F) );

    Matrix4x4 affine{ XMMatrixMultiply(kAdjustSizeScaling, kAdjustOrigin) };
    affine = XMMatrixMultiply( affine, kScaling );
    affine = XMMatrixMultiply( affine, kRotation );
    affine = XMMatrixMultiply( affine, kTranslation );
    affine = XMMatrixMultiply( affine, normalize );
    
    return affine;
}


 // メッシュの作成
 //
 // return true:成功　false:失敗
 //
 // この関数を呼び出す時点で、シェーダーのロードが完了している必要がある
bool Sprite::createMesh()
{
    using namespace Microsoft::WRL;

    // 頂点バッファの作成
    auto d3d_device = EasyEngine::getRenderingManager()->getD3DDevice();
    D3D11_BUFFER_DESC buffer_desc{};
    D3D11_SUBRESOURCE_DATA srd{};
    ComPtr<ID3D11Buffer> buffer{};
     // 頂点座標
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.ByteWidth = sizeof(VertexPositionType)*kVertexPositions.size();
    srd.pSysMem = kVertexPositions.data();
    auto hr = d3d_device->CreateBuffer( &buffer_desc, &srd, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexPosition>(buffer);
     // UV座標
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.ByteWidth = sizeof(VertexUVType)*kVertexPositions.size();
    hr = d3d_device->CreateBuffer( &buffer_desc, nullptr, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexUV>(buffer);
     // インデックス
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.ByteWidth = sizeof(UINT)*kVertexIndices.size();
    srd.pSysMem = kVertexIndices.data();
    hr = d3d_device->CreateBuffer( &buffer_desc, &srd, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexIndex>(buffer);

    // サブメッシュの追加
    mesh_.sub_mesh_list.emplace_back(
        SubMesh{ shader_.get(),
                 Material{},
                 kVertexIndices.size(),
                 0,
                 0 } 
    );

    return true;
}


 // テクスチャのロード
 //
 // in FilePath : ロードするテクスチャのパス
 //
 // return true:成功　false:失敗
 //
 // この関数が呼び出される時点で、メッシュが作成されている必要がある。
bool Sprite::loadTexture( const std::string& FilePath )
{
    // ロード
    auto* texture_loader = EasyEngine::getRenderingManager()->getTextureLoader();
    auto texture = texture_loader->load( FilePath );
    if( !texture ) return false;
    mesh_.sub_mesh_list.at(0).material.set<TagMaterialDiffuseTexture>( texture.get() );

    // テクスチャ情報を抜き出す
    Microsoft::WRL::ComPtr<ID3D11Resource> resource{};
    texture.get()->GetResource( &resource );
    D3D11_TEXTURE2D_DESC tex_desc{};
    static_cast<ID3D11Texture2D*>(resource.Get())->GetDesc(&tex_desc);
    texture_width_ = static_cast<float>(tex_desc.Width);
    texture_height_= static_cast<float>(tex_desc.Height);

    return true;
}


 // コンポーネントを初期化
 //
 // Transform2DComponent
 // RenderingComponent   をデフォルトで追加している。
void Sprite::initComponent()
{
    addComponent<Transform2DComponent>();
    auto* render = addComponent<RenderingComponent>();
    render->setMesh( mesh_ );
}



 // タスクを登録
void Sprite::registerTask()
{
    task_.setJob( this, &Sprite::update );
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kActorUpdate );
}

END_EGEG
// EOF
