// �쐬�� : ��
#include "sprite_vertex_shader.hpp"

USING_NS_EGEG;

// ���_�f�[�^�̃o�C���h
DetailedResult<BindedVertexData> SpriteVertexShader::bindVertices( const Vertex& Vertices ) const
{
    using RetTy = DetailedResult<BindedVertexData>;
    
    // �f�[�^�̐��������m�F
    if( !Vertices.get<Tag_VertexPosition>() )
        return RetTy( Failure(), "���_���W������܂���B" );
    if( !Vertices.get<Tag_VertexUV>() )
        return RetTy( Failure(), "UV���W������܂���" );

    // �o��
    BindedVertexData binded;
     // ���_���W
    binded.buffers.push_back( Vertices.get<Tag_VertexPosition>().Get() );
    binded.strides.push_back( sizeof(VertexPositionType) );
    binded.offsets.push_back( 0U );
     // UV���W
    binded.buffers.push_back( Vertices.get<Tag_VertexUV>().Get() );
    binded.strides.push_back( sizeof(VertexUVType) );
    binded.offsets.push_back( 0U );
    return RetTy( Success(), std::move(binded) );
}

// ���_�V�F�[�_�\�X�e�[�W�̍\��
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
