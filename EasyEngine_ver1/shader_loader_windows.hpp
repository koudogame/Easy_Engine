///
/// @file   shader_loader_windows.hpp
/// @author 板場
///
/// @brief  Windows用シェーダーローダー
///
#ifndef INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "shader_loader.hpp"
BEGIN_EGEG
class ShaderLoaderWindows :
    public IShaderLoader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pDevice : D3Dデバイス
    ///
    ShaderLoaderWindows( ID3D11Device* pDevice );

// IShaderLoader
/*-----------------------------------------------------------------*/
    bool loadVertexShader( const char*, IVertexShader** ) override;
    bool loadGeometryShader( const char*, IGeometryShader** ) override;
    bool loadPixelShader( const char*, IPixelShader** ) override;

private :
    ~ShaderLoaderWindows();
    ID3D11Device* p_device_;    /// D3Dデバイス
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHADER_LOADER_WINDOWS_HEADER_
/// EOF
