// 作成者 : 板場
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
 // 頂点シェーダ―の読み込み
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
        return { Failure{}, "シェーダ―オブジェクトの生成に失敗\n ファイル名: " + FilePath };
    ComPtr<ID3D11InputLayout> il{};
    if( !createIL(*blob, InputDescs, &il) )
        return { Failure{}, "頂点入力レイアウトの生成に失敗\n ファイル名: " + FilePath };

    *VSOut = vs.Get(); vs->AddRef();
    *ILOut = il.Get(); il->AddRef();
    return Success{};
}


 // ジオメトリシェーダ―の読み込み
DetailedReturnValue<bool>
ShaderLoader::loadGeometryShader( const std::string& FilePath, ID3D11GeometryShader** GSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs{};
    if( !createGS(*blob, &gs) )
        return { Failure{}, "シェーダーオブジェクトの生成に失敗\n ファイル名: " + FilePath };

    *GSOut = gs.Get(); gs->AddRef();
    return Success{};
}


 // ピクセルシェーダ―の読み込み
DetailedReturnValue<bool>
ShaderLoader::loadPixelShader( const std::string& FilePath, ID3D11PixelShader** PSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11PixelShader> ps{};
    if( !createPS(*blob, &ps) )
        return { Failure{}, "シェーダーオブジェクトの生成に失敗\n ファイル名: " + FilePath };

    *PSOut = ps.Get(); ps->AddRef();
    return Success{};
}


 // コンピュートシェーダ―の読み込み
DetailedReturnValue<bool>
ShaderLoader::loadComputeShader( const std::string& FilePath, ID3D11ComputeShader** CSOut ) const
{
    auto blob = loadBinary( FilePath );
    if( !blob )
        return { Failure{}, blob.what() };

    Microsoft::WRL::ComPtr<ID3D11ComputeShader> cs{};
    if( !createCS(*blob, &cs) )
        return { Failure{}, "シェーダ―オブジェクトの生成に失敗\n ファイル名: " + FilePath };

    *CSOut = cs.Get(); cs->AddRef();
    return Success{};
}


 // 頂点入力レイアウトの生成
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


 // 頂点シェーダ―の生成
bool ShaderLoader::createVS( const BinaryData& Blob, ID3D11VertexShader** VSOut) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateVertexShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        VSOut)
    );
}


 // ジオメトリシェーダ―の生成
bool ShaderLoader::createGS( const BinaryData& Blob, ID3D11GeometryShader** GSOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreateGeometryShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        GSOut)
    );
}


 // ピクセルシェーダ―の生成
bool ShaderLoader::createPS( const BinaryData& Blob, ID3D11PixelShader** PSOut ) const
{
    return SUCCEEDED( getManager()->getD3DDevice()->CreatePixelShader(
        Blob.bytecode,
        Blob.length,
        nullptr,
        PSOut)
    );
}


 // コンピュートシェーダ―の生成
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
 // ファイルからバイナリコードを読み込む
DetailedReturnValue<ShaderLoader::BinaryData>
loadBinary( const std::string& FilePath )
{
    std::fstream stream{ FilePath, std::ios::binary | std::ios::in };
    if( !stream )
        return { Failure{}, "ファイルのオープンに失敗\n ファイル名: " + FilePath };

    // シェーダ―コードのサイズを取得する
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
