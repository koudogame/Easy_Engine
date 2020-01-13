///
/// @file   texture_loader_d3d11.hpp
/// @author ��
///
/// @brief  D3D11�p�e�N�X�`�����[�_�[
///
#ifndef INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
#define INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
#include "texture_loader.hpp"
#include <unordered_map>
#include <d3d11.h>
BEGIN_EGEG
class TextureLoaderD3D11 :
    public ITextureLoader
{
public :
    TextureLoaderD3D11( ID3D11Device* pDevice ) :
        p_device_( pDevice )
    {
        p_device_->AddRef();
    }


private :
// ITextureLoader
/*-----------------------------------------------------------------*/
    bool loadFromFile( const wchar_t*, ITexture** ) override;

    ~TextureLoaderD3D11()
    {
        p_device_->Release();
    }

    ID3D11Device* p_device_;    ///< D3D�f�o�C�X
};
END_EGEG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
/// EOF
