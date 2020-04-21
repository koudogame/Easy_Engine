// 作成者 : 板場
#include "sprite_pixel_shader.hpp"

USING_NS_EGEG;

// ピクセルシェーダ―ステージの構成
void SpritePixelShader::setShaderOnPipeline( ID3D11DeviceContext* DC )
{
    DC->PSSetShader( shader_.Get(), nullptr, 0 );
}
void SpritePixelShader::setShaderResourcesOnPipeline( ID3D11DeviceContext* )
{
}
void SpritePixelShader::setConstantBuffersOnPipeline( ID3D11DeviceContext* )
{
}
void SpritePixelShader::setSamplersOnPipeline( ID3D11DeviceContext* )
{
}
void SpritePixelShader::setMaterial( const Material& )
{
}
// EOF
