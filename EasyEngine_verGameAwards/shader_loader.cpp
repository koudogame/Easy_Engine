// 作成者 : 板場
#include "shader_loader.hpp"
#include <fstream>

BEGIN_EGEG

// ShaderLoader 関数実装
/*===========================================================================*/
// ファイルからバイトコードを読み込む
DetailedResult<ShaderLoader::BinaryData> ShaderLoader::loadBinary( const char* FileName )
{
    using RetValTy = DetailedResult<ShaderLoader::BinaryData>;

    //ファイルオープン
    std::fstream stream( FileName, std::ios::binary | std::ios::in );
    if( !stream ) 
        return RetValTy( Failure(), "ファイルのオープンに失敗" );

    // シェーダ―コードを読み込む
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
    
    return RetValTy( Success(), std::move(data) );
}

// インプットレイアウトオブジェクトを生成
bool ShaderLoader::createIL( 
    const BinaryData& Code,
    const D3D11_INPUT_ELEMENT_DESC* InputDescs,
    UINT NumElems, 
    ID3D11InputLayout** Output )
{
    return SUCCEEDED( engine_->getDevice()->CreateInputLayout(
        InputDescs,
        NumElems,
        Code.bytecode,
        Code.length,
        Output
    ));
}

// 頂点シェーダ―オブジェクトを生成
bool ShaderLoader::createVS( const BinaryData& Code, ID3D11VertexShader** Output )
{
    return SUCCEEDED( engine_->getDevice()->CreateVertexShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

// ジオメトリシェーダ―オブジェクトを生成
bool ShaderLoader::createGS( const BinaryData& Code, ID3D11GeometryShader** Output )
{
    return SUCCEEDED( engine_->getDevice()->CreateGeometryShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

// ピクセルシェーダ―オブジェクトを生成
bool ShaderLoader::createPS( const BinaryData& Code, ID3D11PixelShader** Output )
{
    return SUCCEEDED( engine_->getDevice()->CreatePixelShader(
        Code.bytecode,
        Code.length,
        nullptr,
        Output
    ));
}

END_EGEG
// EOF
