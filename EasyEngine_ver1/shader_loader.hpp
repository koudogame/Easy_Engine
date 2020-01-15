///
/// @file   shader_loader.hpp
/// @author 板場
///
/// @brief  シェーダーローダー
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_
#define INCLUDED_EGEG_SHADER_LOADER_
#include "shared_object.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
BEGIN_EGEG
class IShaderLoader :
    public SharedObject
{
public :
    ///
    /// @brief  頂点シェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppVertexShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    virtual bool loadVertexShader( const char* FilePath, IVertexShader** ppVertexShader ) = 0;

    ///
    /// @brief  ジオメトリシェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppGeometryShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    virtual bool loadGeometryShader( const char* FilePath, IGeometryShader** ppGeometryShader ) = 0;

    ///
    /// @brief  ピクセルシェーダ―の読み込み
    ///
    /// @param[in] FilePath : コンパイル済みシェーダーのファイルパス
    /// @param[out] ppPixelShader : 読み込んだシェーダーを受け取るインターフェイス
    ///
    /// @return 読み込みに成功[ true ] 読み込みに失敗[ false ]
    ///
    virtual bool loadPixelShader( const char* FilePath, IPixelShader** ppPixelShader ) = 0;

protected :
    virtual ~IShaderLoader() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_
/// EOF
