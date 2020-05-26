// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "sprite_shader.hpp"
#include "engine.hpp"


BEGIN_EGEG

/******************************************************************************

	constant

******************************************************************************/
namespace
{
    const std::vector<D3D11_INPUT_ELEMENT_DESC> kInputElementDescs
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            1,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };
}


/******************************************************************************

	SpriteShader

******************************************************************************/
 // 生成
std::unique_ptr<SpriteShader> SpriteShader::create()
{
    auto shader = std::make_unique<SpriteShader>();
    auto* renderer = EasyEngine::getRenderingManager();

    // シェーダーファイルを読み込む
     // 頂点シェーダ―
    auto* shader_loader = renderer->getShaderLoader();
    auto result = shader_loader->loadVertexShader( "Resource/Shaders/sprite_vs.cso", kInputElementDescs, &shader->vs_, &shader->il_ );
    if( !result ) return nullptr;
     // ピクセルシェーダ―
    result = shader_loader->loadPixelShader( "Resource/Shaders/sprite_ps.cso", &shader->ps_ );
    if( !result ) return nullptr;

    return shader;
}


 // シェーディング
DetailedReturnValue<bool> SpriteShader::shading(
    ID3D11DeviceContext* DC, 
    const VertexData& Vertices, 
    const Material& Material)
{
    // 頂点の正当性を確認
    if( !Vertices.get<TagVertexPosition>() )
        return { Failure{}, "頂点座標用バッファがありません。" };
    if( !Vertices.get<TagVertexUV>() )
        return { Failure{}, "UV座標用バッファがありません。" };

    // パイプラインを構成
     // 各種シェーダー
    DC->VSSetShader( vs_.Get(), nullptr, 0 );
	DC->PSSetShader( ps_.Get(), nullptr, 0 );
	DC->GSSetShader( nullptr, nullptr, 0 );
	DC->DSSetShader( nullptr, nullptr, 0 );
	DC->HSSetShader( nullptr, nullptr, 0 );
	DC->CSSetShader( nullptr, nullptr, 0 );
     // 頂点
    ID3D11Buffer* buffers[2]{ Vertices.get<TagVertexPosition>().Get(), Vertices.get<TagVertexUV>().Get() };
    UINT strides[2]{ sizeof(VertexPositionType), sizeof(VertexUVType) };
    UINT offsets[2]{ 0U, 0U };
    DC->IASetInputLayout( il_.Get() );
    DC->IASetVertexBuffers( 0, 2, buffers, strides, offsets );
     // テクスチャ
    auto* texture = Material.get<TagMaterialDiffuseTexture>().Get();
    if( !texture )
        return { Failure{}, "テクスチャがありません。" };
    DC->PSSetShaderResources( 0, 1, &texture );

    return Success{};
}

END_EGEG
// EOF
