// �쐬�� : ��
#include "model_pixel_shader.hpp"

USING_NS_EGEG;

// �s�N�Z���V�F�[�_�\�X�e�[�W���\��
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
