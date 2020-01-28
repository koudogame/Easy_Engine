///
/// @file   geometry_shader_d3d11.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
#define INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "geometry_shader.hpp"
BEGIN_EGEG
///
/// @class  GeometryShaderD3D11
///
/// @brief  DirectX11用ジオメトリシェーダー
///
class GeometryShaderD3D11 :
    public IGeometryShader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pGeometryShader : 保持するシェーダーオブジェクト
    ///
    GeometryShaderD3D11( ID3D11GeometryShader* pGeometryShader) :
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
    ~GeometryShaderD3D11()
    {
        p_shader_->Release();
    }
    ID3D11GeometryShader* p_shader_;    /// シェーダーオブジェクト
};
END_EGEG
#endif /// !INCLUDED_EGEG_GEOMETRY_SHADER_D3D11_HEADER_
/// EOF
