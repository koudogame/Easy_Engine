///
/// @file   vertex_shader_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用頂点シェーダー
///
#ifndef INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
#define INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
BEGIN_EG_EG
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
        p_vertex_shader_( pVertexShader )
    {
        p_vertex_shader_->AddRef();
    }

    ///
    /// @brief  保持しているシェーダーオブジェクトを取得します。
    ///
    /// @return 保持しているシェーダーオブジェクトのアドレス
    ///
    ID3D11VertexShader* get() const { return p_vertex_shader_; }

private :
    ~VertexShaderD3D11()
    {
        p_vertex_shader_->Release();
    }

    ID3D11VertexShader* p_vertex_shader_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_VERTEX_SHADER_D3D11_HEADER_
/// EOF
