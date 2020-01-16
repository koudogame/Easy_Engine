///
/// @file   texture_loader_windows.hpp
/// @author 板場
///
/// @brief  Windows用テクスチャローダー
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_WINDOWS_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_WINDOWS_HEADER_
#include <d3d11.h>
#include "texture_loader.hpp"
BEGIN_EGEG
class TextureLoaderWindows :
    public ITextureLoader
{
public :
    ///
    /// @brief  コンストラクタ
    ///
    /// @param[in] pDevice : D3Dデバイス
    ///
    TextureLoaderWindows( ID3D11Device* pDevice );
        
// ITextureLoader
/*-----------------------------------------------------------------*/
    bool load( const std::wstring&, ITexture** ) override;

private :
    ~TextureLoaderWindows();
    ID3D11Device* p_device_;    /// D3Dデバイス
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_WINDOWS_HEADER_
/// EOF
