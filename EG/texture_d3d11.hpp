///
/// @file   texture_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用テクスチャ
///
#ifndef INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
#define INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
#include <d3d11.h>
#include "texture.hpp"
#include "texture_loader_d3d11.hpp"
BEGIN_EG_EG
class TextureD3D11 :
    public ITexture
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pManager : 自身の管理者
    /// @param[in] pView : 保持するシェーダーリソースビュー
    ///
    TextureD3D11( TextureLoaderD3D11* pManager, ID3D11ShaderResourceView* pView ) :
        p_manager_(pManager),
        p_view_(pView)
    {
        p_view_->AddRef();
    }

    ///
    /// @brief  保持しているリソースを取得します。
    ///
    /// @return 保持しているリソースのアドレス
    ///
    ID3D11ShaderResourceView* get() const { return p_view_; }

// ITexture
/*-----------------------------------------------------------------*/

private :
    ~TextureD3D11()
    {
        p_view_->Release();
    }

    TextureLoaderD3D11* p_manager_;
    ID3D11ShaderResourceView* p_view_;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
/// EOF
