///
/// @file   vertex_shader_windows.hpp
/// @author 板場
///
/// @brief  Windows用頂点シェーダー
///
#ifndef INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "vertex_shader.hpp"
BEGIN_EGEG
class VertexShaderWindows :
    public IVertexShader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pVertexShader : 保持するシェーダーオブジェクト
    /// @param[in] pInputLayout  : 頂点入力レイアウト
    ///
    VertexShaderWindows( ID3D11VertexShader* pVertexShader,
                         ID3D11InputLayout*  pInputLayout ) :
        p_shader_( pVertexShader ),
        p_layaut_( pInputLayout )
    {
        p_shader_->AddRef();
        p_layaut_->AddRef();
    }

    ///
    /// @brief   シェーダーオブジェクトの取得
    ///
    /// @return  シェーダーオブジェクト
    ///
    ID3D11VertexShader* getShader() const { p_shader_->AddRef(); return p_shader_; }

    ///
    /// @brief  
    ///

private :
    ~VertexShaderWindows()
    {
        p_layaut_->Release();
        p_shader_->Release();
    }
    ID3D11VertexShader* p_shader_;  /// シェーダーオブジェクト
    ID3D11InputLayout*  p_layaut_;  /// 頂点入力レイアウト
};
END_EGEG
#endif /// !INCLUDED_EGEG_VERTEX_SHADER_WINDOWS_HEADER_
/// EOF
