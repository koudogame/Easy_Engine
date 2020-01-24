///
/// @file   vertex_shader_d3d11.hpp
/// @author 板場
///
/// @brief  DirectX11用頂点シェーダー
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
BEGIN_EGEG
class VertexShaderD3D11 :
    public IVertexShader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pVertexShader : 保持するシェーダーオブジェクト
    ///
    VertexShaderD3D11( ID3D11VertexShader* pVertexShader ) :
        p_shader_( pVertexShader )
    {
        p_shader_->AddRef();
    }

    ///
    /// @brief   シェーダーオブジェクトの取得
    ///
    /// @return  シェーダーオブジェクト
    ///
    ID3D11VertexShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

private :
    ~VertexShaderD3D11()
    {
        p_shader_->Release();
    }
    ID3D11VertexShader* p_shader_;  /// シェーダーオブジェクト
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_D3D11_HEADER_
/// EOF
