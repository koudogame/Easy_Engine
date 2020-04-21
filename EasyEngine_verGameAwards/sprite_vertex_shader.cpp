// 作成者 : 板場
#include "sprite_vertex_shader.hpp"

USING_NS_EGEG;

// 頂点データのバインド
DetailedResult<BindedVertexData> SpriteVertexShader::bindVertices( const Vertex& Vertices ) const
{
    using RetTy = DetailedResult<BindedVertexData>;
    
    // データの正当性を確認
    if( !Vertices.get<Tag_VertexPosition>() )
        return RetTy( Failure(), "頂点座標がありません。" );
    if( !Vertices.get<Tag_VertexUV>() )
        return RetTy( Failure(), "UV座標がありません" );

    // 出力
    BindedVertexData binded;
     // 頂点座標
    binded.buffers.push_back( Vertices.get<Tag_VertexPosition>().Get() );
    binded.strides.push_back( sizeof(VertexPositionType) );
    binded.offsets.push_back( 0U );
     // UV座標
    binded.buffers.push_back( Vertices.get<Tag_VertexUV>().Get() );
    binded.strides.push_back( sizeof(VertexUVType) );
    binded.offsets.push_back( 0U );
    return RetTy( Success(), std::move(binded) );
}

// 頂点シェーダ―ステージの構成
void SpriteVertexShader::setShaderOnPipeline( ID3D11DeviceContext* DC )
{
    DC->VSSetShader( shader_.Get(), nullptr, 0 );
}
void SpriteVertexShader::setShaderResourcesOnPipeline( ID3D11DeviceContext* )
{
}
void SpriteVertexShader::setConstantBuffersOnPipeline( ID3D11DeviceContext* )
{
}
void SpriteVertexShader::setSamplersOnPipeline( ID3D11DeviceContext* )
{
}
void SpriteVertexShader::setMaterial( const Material&  )
{
}

// EOF
