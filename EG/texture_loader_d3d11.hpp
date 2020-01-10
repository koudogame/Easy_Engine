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
BEGIN_EG_EG
class TextureLoaderD3D11 :
    public ITextureLoader
{
public :
    TextureLoaderD3D11( ID3D11Device* pDevice ) :
        p_device_( pDevice )
    {
        p_device_->AddRef();
    }
    
    ///
    /// @brief   �e�N�X�`���̊J���ʒm���󂯎��܂��B
    /// @details �󂯎�����e�N�X�`�����A�L���b�V������폜���܂��B
    /// 
    /// @param[in] Notifier : �ʒm��( �폜�̑Ώێ� )
    ///
    void notifyTextureRelease( ITexture* Notifier );

// ITextureLoader
/*-----------------------------------------------------------------*/
    bool load( const wchar_t*, ITexture** ) override;

private :
    ~TextureLoaderD3D11()
    {
        p_device_->Release();
    }

    ID3D11Device* p_device_;    ///< D3D�f�o�C�X
    std::unordered_map<const wchar_t*, ITexture*> textures_;    ///< �e�N�X�`���L���b�V��
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_TEXTURE_LOADER_D3D11_HEADER_
/// EOF
