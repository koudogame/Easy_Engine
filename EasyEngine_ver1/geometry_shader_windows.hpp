///
/// @file   geometry_shader_windows.hpp
/// @author 板場
///
/// @brief  Windows用ジオメトリシェーダー
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "geometry_shader.hpp"
BEGIN_EGEG
class GeometryShaderWindows :
    public IGeometryShader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pGeometryShader : 保持するシェーダーオブジェクト
    ///
    GeometryShaderWindows( ID3D11GeometryShader* pGeometryShader) :
        p_shader_( pGeometryShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief   シェーダーオブジェクトの取得
    ///
    /// @return  シェーダーオブジェクト
    ///
    ID3D11GeometryShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~GeometryShaderWindows()
    {
        p_shader_->Release();
    }
    ID3D11GeometryShader* p_shader_;    /// シェーダーオブジェクト
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_WINDOWS_HEADER_
/// EOF
