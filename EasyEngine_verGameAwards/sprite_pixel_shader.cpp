// �쐬�� : ��
#include "sprite_pixel_shader.hpp"

USING_NS_EGEG;

// �s�N�Z���V�F�[�_�\�X�e�[�W�̍\��
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
