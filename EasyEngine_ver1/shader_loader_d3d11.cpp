// �쐬�� : ��
#include "shader_loader_d3d11.hpp"
#include <fstream>
#include "vertex_shader_d3d11.hpp"
#include "geometry_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"

namespace
{
    size_t getBinaryLength( std::fstream& FileStream );
} // !unnamed namespace 

BEGIN_EGEG
// ShaderLoaderD3D11
/*===========================================================================*/
// �R���X�g���N�^
ShaderLoaderD3D11::ShaderLoaderD3D11( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}
// �f�X�g���N�^
ShaderLoaderD3D11::~ShaderLoaderD3D11()
{
    p_device_->Release();
}

// ���_�V�F�[�_�\�̓ǂݍ���
bool ShaderLoaderD3D11::loadVertexShader( const std::string& Path, IVertexShader** ppShader )
{
    // �V�F�[�_�[�t�@�C���ǂݍ���
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength(stream);
    char* blob = new char[ file_size ];
    stream.read( blob, file_size );
    stream.close();

    // �V�F�[�_�[�I�u�W�F�N�g�̐���
    ID3D11VertexShader* created_vs;
    if( FAILED(p_device_->CreateVertexShader(blob, file_size, nullptr, &created_vs)) )
    {
        delete[] blob;
        return false;
    }

    // ���_���̓��C�A�E�g
    ID3D11InputLayout* input_layout;
    if( FAILED(p_device_->CreateInputLayout(
        VertexShaderD3D11::kVertexInputLayout,
        sizeof VertexShaderD3D11::kVertexInputLayout / sizeof VertexShaderD3D11::kVertexInputLayout[0],
        blob,
        file_size,
        &input_layout)) )
    {
        created_vs->Release();
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new VertexShaderD3D11( created_vs , input_layout );
    input_layout->Release();
    created_vs->Release();

    return true;
}

// �W�I���g���V�F�[�_�[�̓ǂݍ���
bool ShaderLoaderD3D11::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
{
    // �V�F�[�_�[�t�@�C���̓ǂݍ���
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength( stream );
    char* blob;
    { blob = new char[ file_size ]; }
    stream.read( blob, file_size );
    stream.close();

    // �V�F�[�_�[�I�u�W�F�N�g�̐���
    ID3D11GeometryShader* created_gs;
    if( FAILED(p_device_->CreateGeometryShader(blob, file_size, nullptr, &created_gs)) )
    {
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new GeometryShaderD3D11( created_gs );
    created_gs->Release();

    return true;
}

// �s�N�Z���V�F�[�_�[�̓ǂݍ���
bool ShaderLoaderD3D11::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
{
    // �V�F�[�_�[�t�@�C���̓ǂݍ���
    std::fstream stream( Path, std::ios::binary | std::ios::in );
    if( !stream ) return false;
    size_t file_size = ::getBinaryLength( stream );
    char* blob = new char[ file_size ];
    stream.read( blob, file_size );
    stream.close();

    // �V�F�[�_�[�I�u�W�F�N�g�̐���
    ID3D11PixelShader* created_ps;
    if( FAILED(p_device_->CreatePixelShader(blob, file_size, nullptr, &created_ps)) )
    {
        delete[] blob;
        return false;
    }
    delete[] blob;

    *ppShader = new PixelShaderD3D11( created_ps );
    created_ps->Release();

    return true;
}
END_EGEG

namespace
{
    // �t�@�C���̃T�C�Y���擾����
    // ���̊֐��𔲂�����A�X�g���[���̓t�@�C���n�_���w���B
    //
    // in Stream : �t�@�C���X�g���[��
    //
    // return �t�@�C���̃T�C�Y
    size_t getBinaryLength( std::fstream& Stream )
    {
        Stream.seekg( 0, std::ios::end );
        auto end = Stream.tellg();
        Stream.clear();
        Stream.seekg( 0, std::ios::beg );
        auto beg = Stream.tellg();
        size_t size = static_cast<size_t>( end - beg );

        return size;
    }
} // !unnamed namespace
// EOF
