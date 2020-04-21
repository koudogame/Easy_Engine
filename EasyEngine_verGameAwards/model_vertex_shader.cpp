// �쐬�� : ��
#include "model_vertex_shader.hpp"

USING_NS_EGEG;

// ���_�f�[�^�̃o�C���h
DetailedResult<BindedVertexData> ModelVertexShader::bindVertices( const Vertex& Vertices ) const
{
    using RetTy = DetailedResult<BindedVertexData>;

    // �f�[�^�̐��������m�F
    if( !Vertices.get<Tag_VertexPosition>() )
        return RetTy( Failure(), "���_���W������܂���" );

    // �o��
    BindedVertexData binded;
    binded.buffers.push_back( Vertices.get<Tag_VertexPosition>().Get() );
    binded.strides.push_back( sizeof(VertexPositionType) );
    binded.offsets.push_back( 0 );
    return RetTy( Success(), std::move(binded) );
}

// ���_�V�F�[�_�\�X�e�[�W�̍\��
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
