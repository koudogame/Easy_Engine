// �쐬�� : ��
#include "shader_loader.hpp"
#include <fstream>

BEGIN_EGEG

// ShaderLoader �֐�����
/*===========================================================================*/
// �t�@�C������o�C�g�R�[�h��ǂݍ���
DetailedReturnValue<ShaderLoader::BinaryData> ShaderLoader::loadBinary( const char* FileName )
{
    using RetValTy = DetailedReturnValue<ShaderLoader::BinaryData>;

    //�t�@�C���I�[�v��
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) 
        return RetValTy( false, BinaryData{}, "�t�@�C���̃I�[�v���Ɏ��s" );

    // �V�F�[�_�\�R�[�h��ǂݍ���
    stream.seekg( 0, std::ios::end );
    auto end = stream.tellg();
    stream.clear();
    stream.seekg( 0, std::ios::beg );
    auto beg = stream.tellg();
    BinaryData data;
    data.length = static_cast<size_t>(end - beg);
    data.bytecode = new char[ data.length ];
    stream.read( data.bytecode, data.length );
    stream.close();
    
    return RetValTy( true, std::move(data) );
}

// �C���v�b�g���C�A�E�g�I�u�W�F�N�g�𐶐�
bool ShaderLoader::createIL( 
    const BinaryData& Code,
    const D3D11_INPUT_ELEMENT_DESC* InputDescs,
    UINT NumElems, 
    ID3D11InputLayout** Output )
{
    return SUCCEEDED( device_->CreateInputLayout(
        InputDescs,
        NumElems,
        Code.bytecode,
        Code.length,
        Output
    ));
}

// ���_�V�F�[�_�\�I�u�W�F�N�g�𐶐�
bool ShaderLoader::createVS( const BinaryData& Code, ID3D11VertexShader** Output )
{
    return SUCCEEDED( device_->CreateVertexShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

// �W�I���g���V�F�[�_�\�I�u�W�F�N�g�𐶐�
bool ShaderLoader::createGS( const BinaryData& Code, ID3D11GeometryShader** Output )
{
    return SUCCEEDED( device_->CreateGeometryShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

// �s�N�Z���V�F�[�_�\�I�u�W�F�N�g�𐶐�
bool ShaderLoader::createPS( const BinaryData& Code, ID3D11PixelShader** Output )
{
    return SUCCEEDED( device_->CreatePixelShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

END_EGEG
// EOF
