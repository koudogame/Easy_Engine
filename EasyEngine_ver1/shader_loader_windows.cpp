// �쐬�� : ��
#include "shader_loader_windows.hpp"
#include <fstream>
#include "vertex_shader_windows.hpp"
#include "geometry_shader_windows.hpp"
#include "pixel_shader_windows.hpp"

namespace
{
    size_t loadBinary( const std::string&, char* );
} // !unnamed namespace 

BEGIN_EGEG
// ShaderLoaderWindows
/*===========================================================================*/
// �R���X�g���N�^
ShaderLoaderWindows::ShaderLoaderWindows( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}
// �f�X�g���N�^
ShaderLoaderWindows::~ShaderLoaderWindows()
{
    p_device_->Release();
}

// ���_�V�F�[�_�\�̓ǂݍ���
bool ShaderLoaderWindows::loadVertexShader( const std::string& Path, IVertexShader** ppShader )
{
    ID3D11VertexShader* created_vs;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreateVertexShader(blob, size, nullptr, &created_vs)) )
    {
        delete[] blob;
        return false;
    }

    // ���_���̓��C�A�E�g

    *ppShader = new VertexShaderWindows( created_vs );
    created_vs->Release();

    return true;
}

// �W�I���g���V�F�[�_�[�̓ǂݍ���
bool ShaderLoaderWindows::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
{
    ID3D11GeometryShader* created_gs;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreateGeometryShader(blob, size, nullptr, &created_gs)) )
    {
        delete[] blob;
        return false;
    }

    *ppShader = new GeometryShaderWindows( created_gs );
    created_gs->Release();

    return true;
}

// �s�N�Z���V�F�[�_�[�̓ǂݍ���
bool ShaderLoaderWindows::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
{
    ID3D11PixelShader* created_ps;
    char* blob = nullptr;
    size_t size = ::loadBinary( Path, blob );
    if( size == 0U ||
        FAILED(p_device_->CreatePixelShader(blob, size, nullptr, &created_ps)) )
    {
        delete[] blob;
        return false;
    }

    *ppShader = new PixelShaderWindows( created_ps );
    created_ps->Release();

    return true;
}
END_EGEG

namespace
{
    // �t�@�C������o�C�i���f�[�^��ǂݍ���
    // Buffer�ɂ̓t�@�C���̑傫���ɑΉ������������u���b�N�����蓖�Ă܂��B������Ă��������B
    //
    // in FilePath : �ǂݍ��ރt�@�C���̃p�X
    // out Buffer : �ǂݍ��񂾃f�[�^���i�[����o�b�t�@(�m�ۑO)
    //
    // return �ǂݍ��񂾃t�@�C���̃T�C�Y
    size_t loadBinary( const std::string& FilePath, char* Buffer )
    {
        // �t�@�C���I�[�v��
        std::fstream stream( FilePath, std::ios::binary | std::ios::in );
        if( stream.is_open() == false ) return 0U;

        // �f�[�^�ǂݍ���
        stream.seekg( 0, std::ios::end );
        auto end = stream.tellg();
        stream.clear();
        stream.seekg( 0, std::ios::beg );
        auto beg = stream.tellg();
        size_t size = static_cast<size_t>( end - beg );
        Buffer = new char[ size ];
        stream.read( Buffer, size );
        stream.close();

        return size;
    }
} // !unnamed namespace
// EOF
