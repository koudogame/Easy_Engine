///
/// @file   texture_loader_d3d11.hpp
/// @author 板場
///
/// @brief  D3D11用テクスチャローダー
///
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
#include "texture_loader.hpp"
#include <unordered_map>
#include <d3d11.h>
BEGIN_EG_EG
class TextureLoaderD3D11 :
    public ITextureLoader
{
public :
    TextureLoaderD3D11( ID3D11Device* pDevice ) :
        p_device_( pDevice )
    {}
    
// ITextureLoader
/*-----------------------------------------------------------------*/
    bool load( const wchar_t*, ITexture** ) override;

// Interface
/*-----------------------------------------------------------------*/
    void addRef() override { ++ref_cnt_; }
    void release() override;

private :
    unsigned ref_cnt_ = 0;      ///< 参照数
    ID3D11Device* p_device_;    ///< D3Dデバイス
    std::unordered_map<const wchar_t*, ITexture*> textures_;    ///< テクスチャキャッシュ
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
/// EOF
