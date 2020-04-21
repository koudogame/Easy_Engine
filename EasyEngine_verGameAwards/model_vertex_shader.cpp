// 作成者 : 板場
#include "model_vertex_shader.hpp"

USING_NS_EGEG;

// 頂点データのバインド
DetailedResult<BindedVertexData> ModelVertexShader::bindVertices( const Vertex& Vertices ) const
{
    using RetTy = DetailedResult<BindedVertexData>;

    // データの正当性を確認
    if( !Vertices.get<Tag_VertexPosition>() )
        return RetTy( Failure(), "頂点座標がありません" );

    // 出力
    BindedVertexData binded;
    binded.buffers.push_back( Vertices.get<Tag_VertexPosition>().Get() );
    binded.strides.push_back( sizeof(VertexPositionType) );
    binded.offsets.push_back( 0 );
    return RetTy( Success(), std::move(binded) );
}

// 頂点シェーダ―ステージの構成
void ModelVertexShader::setShaderOnPipeline( ID3D11DeviceContext* DC )
{
    DC->VSSetShader( shader_.Get(), nullptr, 0 );
}
void ModelVertexShader::setShaderResourcesOnPipeline( ID3D11DeviceContext* )
{
}
void ModelVertexShader::setConstantBuffersOnPipeline( ID3D11DeviceContext* )
{
}
void ModelVertexShader::setSamplersOnPipeline( ID3D11DeviceContext* )
{
}
void ModelVertexShader::setMaterial( const Material& )
{
}
// EOF
