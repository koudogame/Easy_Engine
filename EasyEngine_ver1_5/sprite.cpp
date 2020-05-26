// �쐬�� : ��
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
        VertexPositionType{ 0.0F, 0.0F, 0.0F },     // ����
        VertexPositionType{ 1.0F, 0.0F, 0.0F },     // �E��
        VertexPositionType{ 0.0F, -1.0F, 0.0F },    // ����
        VertexPositionType{ 1.0F, -1.0F, 0.0F }     // �E��
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
 // ������
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


 // �I��
void Sprite::finalize()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_ );
}


 // �X�V
void Sprite::update( uint64_t )
{
    // �؂���͈͂���ɁA���_��UV���W���X�V����
    const float kTextureWidthReciprocal = 1.0F / texture_width_;
    const float kTextureHeightReciprocal = 1.0F / texture_height_;
    const float kTrimmingLeft   = trim_base_point_.x * kTextureWidthReciprocal;
    const float kTrimmingTop    = trim_base_point_.y * kTextureHeightReciprocal;
    const float kTrimmingRight  = (trim_base_point_.x+width_)  * kTextureWidthReciprocal;
    const float kTrimmingBottom = (trim_base_point_.y+height_) * kTextureHeightReciprocal;
    const VertexUVType kUVs[4]
    {
        VertexUVType{kTrimmingLeft, kTrimmingTop},      // ����
        VertexUVType{kTrimmingRight, kTrimmingTop},     // �E��
        VertexUVType{kTrimmingLeft, kTrimmingBottom},   // ����
        VertexUVType{kTrimmingRight, kTrimmingBottom}   // �E��
    };

    auto d3d_dc = EasyEngine::getRenderingManager()->getD3DDeviceContext();
    D3D11_MAPPED_SUBRESOURCE mpd{};
    auto hr = d3d_dc->Map(
        mesh_.vertices.get<TagVertexUV>().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mpd );
    if( FAILED(hr) ) return;
    memcpy( mpd.pData, kUVs, sizeof(VertexUVType)*kVertexPositions.size() );
    d3d_dc->Unmap( mesh_.vertices.get<TagVertexUV>().Get(), 0 );

}


 // ���[���h�ϊ��s����v�Z
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


 // ���b�V���̍쐬
 //
 // return true:�����@false:���s
 //
 // ���̊֐����Ăяo�����_�ŁA�V�F�[�_�[�̃��[�h���������Ă���K�v������
bool Sprite::createMesh()
{
    using namespace Microsoft::WRL;

    // ���_�o�b�t�@�̍쐬
    auto d3d_device = EasyEngine::getRenderingManager()->getD3DDevice();
    D3D11_BUFFER_DESC buffer_desc{};
    D3D11_SUBRESOURCE_DATA srd{};
    ComPtr<ID3D11Buffer> buffer{};
     // ���_���W
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.ByteWidth = sizeof(VertexPositionType)*kVertexPositions.size();
    srd.pSysMem = kVertexPositions.data();
    auto hr = d3d_device->CreateBuffer( &buffer_desc, &srd, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexPosition>(buffer);
     // UV���W
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.ByteWidth = sizeof(VertexUVType)*kVertexPositions.size();
    hr = d3d_device->CreateBuffer( &buffer_desc, nullptr, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexUV>(buffer);
     // �C���f�b�N�X
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.ByteWidth = sizeof(UINT)*kVertexIndices.size();
    srd.pSysMem = kVertexIndices.data();
    hr = d3d_device->CreateBuffer( &buffer_desc, &srd, &buffer );
    if( FAILED(hr) ) return false;
    mesh_.vertices.set<TagVertexIndex>(buffer);

    // �T�u���b�V���̒ǉ�
    mesh_.sub_mesh_list.emplace_back(
        SubMesh{ shader_.get(),
                 Material{},
                 kVertexIndices.size(),
                 0,
                 0 } 
    );

    return true;
}


 // �e�N�X�`���̃��[�h
 //
 // in FilePath : ���[�h����e�N�X�`���̃p�X
 //
 // return true:�����@false:���s
 //
 // ���̊֐����Ăяo����鎞�_�ŁA���b�V�����쐬����Ă���K�v������B
bool Sprite::loadTexture( const std::string& FilePath )
{
    // ���[�h
    auto* texture_loader = EasyEngine::getRenderingManager()->getTextureLoader();
    auto texture = texture_loader->load( FilePath );
    if( !texture ) return false;
    mesh_.sub_mesh_list.at(0).material.set<TagMaterialDiffuseTexture>( texture.get() );

    // �e�N�X�`�����𔲂��o��
    Microsoft::WRL::ComPtr<ID3D11Resource> resource{};
    texture.get()->GetResource( &resource );
    D3D11_TEXTURE2D_DESC tex_desc{};
    static_cast<ID3D11Texture2D*>(resource.Get())->GetDesc(&tex_desc);
    texture_width_ = static_cast<float>(tex_desc.Width);
    texture_height_= static_cast<float>(tex_desc.Height);

    return true;
}


 // �R���|�[�l���g��������
 //
 // Transform2DComponent
 // RenderingComponent   ���f�t�H���g�Œǉ����Ă���B
void Sprite::initComponent()
{
    addComponent<Transform2DComponent>();
    auto* render = addComponent<RenderingComponent>();
    render->setMesh( mesh_ );
}



 // �^�X�N��o�^
void Sprite::registerTask()
{
    task_.setJob( this, &Sprite::update );
    EasyEngine::getTaskManager()->registerJob( &task_, TaskOrder::kActorUpdate );
}

END_EGEG
// EOF
