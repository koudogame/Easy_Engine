// �쐬�� : ��
#include "shader_loader.hpp"
#include <fstream>

namespace
{
    size_t getFileSize( std::fstream& );
} // unnamed namespace

BEGIN_EGEG

// ShaderLoader �֐�����
/*===========================================================================*/
// ���_�V�F�[�_�[�̃��[�h
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, const D3D11_INPUT_ELEMENT_DESC* InputElementDescs, size_t NumElements, ID3D11VertexShader** OutShader, ID3D11InputLayout** OutInputLayout )
{
    // �t�@�C���I�[�v��
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "�V�F�[�_�\�t�@�C���̃I�[�v�����s" );

    // �V�F�[�_�[�ǂݍ���
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[filesize];
    stream.read( blob, filesize );
    stream.close();

    // �V�F�[�_�[�I�u�W�F�N�g�̐���
    HRESULT hr = device_->CreateVertexShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    if( FAILED(hr) )
    {
        delete[] blob;
        return ReturnValue( false, "�V�F�[�_�[�I�u�W�F�N�g�̐������s" );
    }

    // ���_���̓��C�A�E�g�I�u�W�F�N�g�̐���
    hr = device_->CreateInputLayout(
        InputElementDescs,
        NumElements,
        blob,
        filesize,
        OutInputLayout );
    if( FAILED(hr) )
    {
        delete[] blob;
        return ReturnValue( false, "���̓��C�A�E�g�I�u�W�F�N�g�̐������s" );
    }

    delete[] blob;
    return true;
}

// �W�I���g���V�F�[�_�[�̃��[�h
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, ID3D11GeometryShader** OutShader )
{
    // �t�@�C���I�[�v��
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "�V�F�[�_�\�t�@�C���̃I�[�v�����s" );

    // �V�F�[�_�\�ǂݍ���
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[ filesize ];
    stream.read( blob, filesize );
    stream.close();

    // �V�F�[�_�\�I�u�W�F�N�g�̐���
    HRESULT hr = device_->CreateGeometryShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    delete[] blob;
    if( FAILED(hr) ) return ReturnValue( false, "�V�F�[�_�\�I�u�W�F�N�g�̐������s" );

    return true;
}

// �s�N�Z���V�F�[�_�[�̃��[�h
DetailedReturnValue<bool> ShaderLoader::load( const TCHAR* FileName, ID3D11PixelShader** OutShader )
{
    // �t�@�C���I�[�v��
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) return ReturnValue( false, "�V�F�[�_�[�t�@�C���̃I�[�v�����s" );

    // �V�F�[�_�\�ǂݍ���
    size_t filesize = ::getFileSize( stream );
    char* blob = new char[ filesize ];
    stream.read( blob, filesize );
    stream.close();

    // �V�F�[�_�[�I�u�W�F�N�g�̐���
    HRESULT hr = device_->CreatePixelShader(
        blob,
        filesize,
        nullptr,
        OutShader );
    delete[] blob;
    if( FAILED(hr) ) return ReturnValue( false, "�V�F�[�_�[�I�u�W�F�N�g�̐������s" );

    return true;
}
END_EGEG


namespace
{
// �t�@�C���T�C�Y�̎擾
// �����̃t�@�C���X�g���[���͊��Ƀt�@�C�����J���Ă�����̂Ƃ���B
// ���̊֐��𔲂�����A�X�g���[���̓t�@�C���n�_���w���B
//
// in Stream : �T�C�Y���擾����t�@�C���X�g���[��
//
// return �t�@�C���T�C�Y
size_t getFileSize( std::fstream& Stream )
{
    Stream.seekg( 0, std::ios::end );
    auto end = Stream.tellg();
    Stream.clear();
    Stream.seekg( 0, std::ios::beg );
    auto beg = Stream.tellg();
    
    return static_cast<size_t>( end - beg );
}
} // unnamed namespace
// EOF
