// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "shader_loader.hpp"
#include "rendering_manager.hpp"
#include "fstream"


BEGIN_EGEG

/******************************************************************************

	declaration

******************************************************************************/
DetailedReturnValue<ShaderLoader::BinaryData> loadBinary( const std::string& );


/******************************************************************************

	ShaderLoader

******************************************************************************/
 // ���_�V�F�[�_�\�̓ǂݍ���
DetailedReturnValue<bool>
ShaderLoader::loadVertexShader(
    const std::string& FilePath,
    const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputDescs,
    ID3D11VertexShader** VSOut,
    ID3D11InputLayout** ILOut ) const
{
    using namespace Microsoft::WRL;

    auto blob = loadBinary( FilePath );
    if( !blob ) 
        return { Failure{}, blob.what() };

    ComPtr<ID3D11VertexShader> vs{};
    if( !createVS(*blob, &vs) )
        return { Failure{}, "�V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s\n �t�@�C����: " + FilePath };
    ComPtr<ID3D11InputLayout> il{};
    if( !createIL(*blob, InputDescs, &il) )
        return { Failure{}, "���_���̓��C�A�E�g�̐����Ɏ��s\n �t�@�C����: " + FilePath };

    *VSOut = vs.Get(); vs->AddRef();
    *ILOut = il.Get(); il->AddRef();
    return Success{};
}


 // �W�I���g���V�F�[�_�\�̓ǂݍ���
DetailedReturnValue<bool>
ShaderLoader::loadGeometryShader( const std::string& FilePath, ID3D11GeometryShader** GSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs{};
    if( !createGS(*blob, &gs) )
        return { Failure{}, "�V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s\n �t�@�C����: " + FilePath };

    *GSOut = gs.Get(); gs->AddRef();
    return Success{};
}


 // �s�N�Z���V�F�[�_�\�̓ǂݍ���
DetailedReturnValue<bool>
ShaderLoader::loadPixelShader( const std::string& FilePath, ID3D11PixelShader** PSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11PixelShader> ps{};
    if( !createPS(*blob, &ps) )
        return { Failure{}, "�V�F�[�_�[�I�u�W�F�N�g�̐����Ɏ��s\n �t�@�C����: " + FilePath };

    *PSOut = ps.Get(); ps->AddRef();
    return Success{};
}


 // �R���s���[�g�V�F�[�_�\�̓ǂݍ���
DetailedReturnValue<bool>
ShaderLoader::loadComputeShader( const std::string& FilePath, ID3D11ComputeShader** CSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11ComputeShader> cs{};
    if( !createCS(*blob, &cs) )
        return { Failure{}, "�V�F�[�_�\�I�u�W�F�N�g�̐����Ɏ��s\n �t�@�C����: " + FilePath };

    *CSOut = cs.Get(); cs->AddRef();
    return Success{};
}


 // ���_���̓��C�A�E�g�̐���
bool ShaderLoader::createIL(
    const BinaryData& Blob,
    const std::vector<D3D11_INPUT_ELEMENT_DESC>& Descs,
    ID3D11InputLayout** ILOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateInputLayout(
        Descs.data(),
        Descs.size(),
        Blob.bytecode,
        Blob.length,
        ILOut)
    );
}


 // ���_�V�F�[�_�\�̐���
bool ShaderLoader::createVS( const BinaryData& Blob, ID3D11VertexShader** VSOut) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateVertexShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        VSOut)
    );
}


 // �W�I���g���V�F�[�_�\�̐���
bool ShaderLoader::createGS( const BinaryData& Blob, ID3D11GeometryShader** GSOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateGeometryShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        GSOut)
    );
}


 // �s�N�Z���V�F�[�_�\�̐���
bool ShaderLoader::createPS( const BinaryData& Blob, ID3D11PixelShader** PSOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreatePixelShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        PSOut)
    );
}


 // �R���s���[�g�V�F�[�_�\�̐���
bool ShaderLoader::createCS( const BinaryData& Blob, ID3D11ComputeShader** CSOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateComputeShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        CSOut)
    );
}


/******************************************************************************

	others

******************************************************************************/
 // �t�@�C������o�C�i���R�[�h��ǂݍ���
DetailedReturnValue<ShaderLoader::BinaryData>
loadBinary( const std::string& FilePath )
{
    std::fstream stream{ FilePath, std::ios::binary | std::ios::in };
    if( !stream )
        return { Failure{}, "�t�@�C���̃I�[�v���Ɏ��s\n �t�@�C����: " + FilePath };

    // �V�F�[�_�\�R�[�h�̃T�C�Y���擾����
    stream.seekg( 0, std::ios::end );
    auto kEndPos = stream.tellg();
    stream.clear();
    stream.seekg( 0, std::ios::beg );
    auto kBegPos = stream.tellg();

    ShaderLoader::BinaryData blob{};
    blob.length = static_cast<size_t>(kEndPos - kBegPos);
    blob.bytecode = new char[ blob.length ];
    stream.read( blob.bytecode, blob.length );
    stream.close();

    return { Success{}, std::move(blob) };
}


END_EGEG
// EOF
