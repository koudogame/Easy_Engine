///
/// @file   texture_windows.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#define INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#include <d3d11.h>
#include "texture.hpp"
BEGIN_EGEG
///
/// @class  TextureD3D11
///
/// @brief  DirectX11用テクスチャ
///
class TextureD3D11 :
    public ITexture
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pTexture : 保持するシェーダーリソースビュー
    ///
    TextureD3D11( ID3D11ShaderResourceView* pTexture ) :
        p_texture_( pTexture )
    {
        p_texture_->AddRef();

        /// テクスチャサイズの取得
        ID3D11Resource* resource;
        p_texture_->GetResource( &resource );

        D3D11_TEXTURE2D_DESC tex_desc;
        static_cast<ID3D11Texture2D*>(resource)->GetDesc( &tex_desc );
        width_ = tex_desc.Width;
        height_ = tex_desc.Height;

        resource->Release();
    }

    ///
    /// @brief  シェーダーリソースビューの取得
    ///
    /// @return 保持しているシェーダーリソースビュー
    ///
    ID3D11ShaderResourceView* getShaderResourceView() const { p_texture_->AddRef(); return p_texture_; }

// ITexture
/*-----------------------------------------------------------------*/
    long getWidth()  const override { return width_; }
    long getHeight() const override { return height_; }

private :
    ~TextureD3D11()
    {
        p_texture_->Release();
    }
    ID3D11ShaderResourceView* p_texture_;   /// シェーダーリソースビュー
    long width_;
    long height_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
/// EOF
