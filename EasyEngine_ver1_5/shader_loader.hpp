///
/// @file   shader_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_HEADER_

#include <vector>
#include <d3d11.h>
#include "rendering_manager_child.hpp"
#include "return_value.hpp"

BEGIN_EGEG

///
/// @class ShaderLoader
/// @brief シェーダーローダー
///
class ShaderLoader :
    public RenderingManagerChild
{
public :
    using RetTy = DetailedReturnValue<bool>;

    ///
    /// @brief 頂点シェーダ―の読み込み
    ///
    /// @param[in] CompiledShaderFilePath : 読み込むコンパイル済みシェーダ―ファイルのパス
    /// @param[in] InputDescs             : 頂点入力レイアウト配列
    /// @param[out] VSOUt                 : 頂点シェーダ―出力先
    /// @param[out] ILOut                 : 頂点入力レイアウト出力先
    ///
    /// @return true:成功　false:失敗
    ///
    RetTy loadVertexShader( 
        const std::string& CompiledShaderFilePath, 
        const std::vector<D3D11_INPUT_ELEMENT_DESC>& InputDescs,
        ID3D11VertexShader** VSOut, ID3D11InputLayout** ILOut ) const;

    ///
    /// @brief  ジオメトリシェーダーのロード
    ///
    /// @param[in] CompiledShaderFilePath : 読み込むコンパイル済シェーダ―ファイルパス
    /// @param[out] GSOut                 : ジオメトリシェーダー出力先
    ///
    /// @return true:成功　false:失敗
    ///
    RetTy loadGeometryShader( 
        const std::string& CompiledShaderFilePath,
        ID3D11GeometryShader** GSOut ) const;

    ///
    /// @brief  ピクセルシェーダ―のロード
    ///
    /// @param[in] CompiledShaderFilePath : 読み込むコンパイル済みシェーダ―ファイルパス
    /// @param[out] PSOut                 : ピクセルシェーダ―出力先
    ///
    /// @return true:成功　false:失敗
    ///
    RetTy loadPixelShader(
        const std::string& CompiledShaderFilePath,
        ID3D11PixelShader** PSOut ) const;
    
    ///
    /// @brief  コンピュートシェーダ―のロード
    ///
    /// @param[in] CompiledShaderFilePath : 読み込むコンパイル済みシェーダ―ファイルパス
    /// @param[out] CSOut                 : コンピュートシェーダ―出力先
    ///
    /// @return true:成功　false:失敗
    ///
    RetTy loadComputeShader(
        const std::string& CompiledShaderFilePath,
        ID3D11ComputeShader** CSOut ) const;


    struct BinaryData
    {
        BinaryData() = default;
        ~BinaryData() { delete[] bytecode; }
        BinaryData( BinaryData&& Rhs ) noexcept:
            length{ Rhs.length },
            bytecode{ Rhs.bytecode }
        {
            Rhs.length = 0;
            Rhs.bytecode = nullptr;
        }
        size_t length{ 0 };
        char* bytecode{ nullptr };
    };
private :
    bool createIL( const BinaryData&, const std::vector<D3D11_INPUT_ELEMENT_DESC>&, ID3D11InputLayout** ) const;
    bool createVS( const BinaryData&, ID3D11VertexShader** ) const;
    bool createGS( const BinaryData&, ID3D11GeometryShader** ) const;
    bool createPS( const BinaryData&, ID3D11PixelShader** ) const;
    bool createCS( const BinaryData&, ID3D11ComputeShader** ) const;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_HEADER_
/// EOF
