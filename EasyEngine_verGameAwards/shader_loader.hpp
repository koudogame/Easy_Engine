///
/// @file   shader_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_HEADER_
#include <unordered_map>
#include "loader.hpp"
#include "egeg_utility.hpp"
BEGIN_EGEG
///
/// @class  ShaderLoader
/// @brief  シェーダーローダー
///
class ShaderLoader :
    public Loader
{
public :
    using ReturnValue = DetailedReturnValue<bool>;

    ShaderLoader( const std::shared_ptr<RenderingEngine>& Engine ) :
        Loader( Engine )
    {}

    ///
    /// @brief  頂点シェーダーの読み込み
    ///
    /// @param[in] FileName          : コンパイル済みシェーダーファイル名
    /// @param[in] InputElementDescs : 頂点入力レイアウトを構成する配列
    /// @param[in] NumElements       : InputElementDescs配列の要素数
    /// @param[out] OutShader        : 生成したシェーダーオブジェクトを格納するポインタ
    /// @param[out] OutInputLayout   : 生成した頂点入力レイアウトオブジェクトを格納するポインタ
    ///
    /// @return 読み込み成功[ true ]　読み込み失敗[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, const D3D11_INPUT_ELEMENT_DESC* InputElementDescs, size_t NumElements, ID3D11VertexShader** OutShader, ID3D11InputLayout** OutInputLayout );
    ///
    /// @brief  ジオメトリシェーダーの読み込み
    ///
    /// @param[in] FileName   : コンパイル済みシェーダーファイル名
    /// @param[out] OutShader : 生成したシェーダーオブジェクトを格納するポインタ
    ///
    /// @return 読み込み成功[ true ]　読み込み失敗[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, ID3D11GeometryShader** OutShader );
    ///
    /// @brief  ピクセルシェーダーの読み込み
    ///
    /// @param[in] FileName : コンパイル済みシェーダーファイル名
    /// @param[out] OutShader : 生成したシェーダーオブジェクトを格納するポインタ
    ///
    /// @return 読み込み成功[ true ]　読み込み失敗[ false ]
    ///
    ReturnValue load( const TCHAR* FileName, ID3D11PixelShader** OutShader );
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
