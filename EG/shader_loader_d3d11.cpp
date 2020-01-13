// �쐬�� : ��
#include "shader_loader_d3d11.hpp"
#include <fstream>
#include "vertex_shader_d3d11.hpp"
#include "pixel_shader_d3d11.hpp"

BEGIN_EGEG
// �֐��̎���
/*===========================================================================*/
// ���_�V�F�[�_�\�̃��[�h
bool ShaderLoaderD3D11::loadVertexShader( const char* Path, IVertexShader** ppOut )
{
    auto find = vertex_shaders_.find( Path );

    // �L���b�V���ɂ���ꍇ
    if( find != vertex_shaders_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �t�@�C���I�[�v��
        std::fstream stream( Path, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return false;

        // �f�[�^�ǂݍ���
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>(end - beg );
        char* blob = new char[size];
        stream.read( blob, size );
        stream.close();

        // ���_�V�F�[�_�\�̐���
        ID3D11VertexShader* p_d3d11vs;
        if( FAILED(p_device_->CreateVertexShader(blob, size, nullptr, &p_d3d11vs)) )
            return false;

        VertexShaderD3D11 *p_vs = new VertexShaderD3D11( p_d3d11vs );
        p_d3d11vs->Release();

        *ppOut = p_vs;
    }

    return true;
}

// �s�N�Z���V�F�[�_�[�̃��[�h
bool ShaderLoaderD3D11::loadPixelShader( const char* Path, IPixelShader** ppOut )
{
    auto find = pixel_shaders_.find( Path );

    // �L���b�V���ɂ���ꍇ
    if( find != pixel_shaders_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �t�@�C���I�[�v��
        std::fstream stream( Path, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return false;

        // �f�[�^�ǂݍ���
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        UINT size = static_cast<UINT>( end - beg );
        char* blob = new char[size];
        stream.read( blob, size );
        stream.close();

        // �s�N�Z���V�F�[�_�\�̍쐬
        ID3D11PixelShader* p_d3d11ps;
        if( FAILED(p_device_->CreatePixelShader(blob, size, nullptr, &p_d3d11ps)) )
            return false;

        PixelShaderD3D11 *p_ps = new PixelShaderD3D11( p_d3d11ps );
        p_d3d11ps->Release();

        *ppOut = p_ps;
    }

    return true;
}
END_EGEG
// EOF
