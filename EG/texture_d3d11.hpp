///
/// @file   texture_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用テクスチャ
///
#ifndef INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
#define INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
#include "texture.hpp"
#include <d3d11.h>
BEGIN_EG_EG
class TextureD3D11 :
    public ITexture
{
public :
    TextureD3D11( ID3D11ShaderResourceView* View ) :
        view_(View)
    {
        view_->AddRef();
    }

// ITexture
/*-----------------------------------------------------------------*/

// Interface
/*-----------------------------------------------------------------*/
    void addRef() override { ++ref_cnt_; }
    void release() override
    {
        if( --ref_cnt_ <= 0 )
        {
            view_->Release();
            delete this;
        }
    }

private :
    unsigned ref_cnt_;
    ID3D11ShaderResourceView* view_ = nullptr;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_D3D11_HEADER_
/// EOF
