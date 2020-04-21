// 作成者 : 板場
#include "model_pixel_shader.hpp"

USING_NS_EGEG;

// ピクセルシェーダ―ステージを構成
void ModelPixelShader::setShaderOnPipeline( ID3D11DeviceContext* DC )
{
    DC->PSSetShader( shader_.Get(), nullptr, 0 );
}
void ModelPixelShader::setShaderResourcesOnPipeline( ID3D11DeviceContext* )
{
}
void ModelPixelShader::setConstantBuffersOnPipeline( ID3D11DeviceContext* )
{
}
void ModelPixelShader::setSamplersOnPipeline( ID3D11DeviceContext* )
{
}
void ModelPixelShader::setMaterial( const Material& )
{
}
// EOF
