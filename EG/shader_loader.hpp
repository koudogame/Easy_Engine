///
/// @file   shader_loader.hpp
/// @author 板場
///
/// @brief  シェーダーローダーのインターフェイス
///
#ifndef INCLUDED_EG_EG_SHADER_LOADER_HEADER_
#define INCLUDED_EG_EG_SHADER_LOADER_HEADER_
#include "interface.hpp"
#include "vertex_shader.hpp"
#include "pixel_shader.hpp"
BEGIN_EG_EG
class IShaderLoader :
    public Interface
{
public :
    ///
    /// @brief  頂点シェーダーのロード
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーファイルのパス
    /// @param[out] ppOutShader : ロードしたシェーダ―を受け取るインターフェイス
    ///
    /// @return ロードに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    virtual bool loadVertexShader( const char* FilePath, IVertexShader** ppOutShader ) = 0;

    ///
    /// @brief  ピクセルシェーダ－のロード
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーファイルのパス
    /// @param[out] ppOutShader : ロードしたシェーダーを受け取るインターフェイス
    ///
    /// @return ロードに成功した場合[ true ] 失敗した場合[ false ]を返却します。
    ///
    virtual bool loadPixelShader( const char* FilePath, IPixelShader** ppOutShader ) = 0;

protected :
    virtual ~IShaderLoader() = default;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_SHADER_LOADER_HEADER_
/// EOF
