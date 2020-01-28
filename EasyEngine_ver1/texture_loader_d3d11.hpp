///
/// @file   texture_loader_d3d11.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TEXTURE_LOADER_D3D11_HEADER_
#define INCLUDED_EGEG_TEXTURE_LOADER_D3D11_HEADER_
#include <d3d11.h>
#include "texture_loader.hpp"
BEGIN_EGEG
///
/// @class  TextureLoaderD3D11
///
/// @brief  DirectX11�p�e�N�X�`�����[�_�[
///
class TextureLoaderD3D11 :
    public ITextureLoader
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pDevice : D3D�f�o�C�X
    ///
    TextureLoaderD3D11( ID3D11Device* pDevice );
        
// ITextureLoader
/*-----------------------------------------------------------------*/
    bool load( const std::wstring&, ITexture** ) override;

private :
    ~TextureLoaderD3D11();
    ID3D11Device* p_device_;    /// D3D�f�o�C�X
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_LOADER_D3D11_HEADER_
/// EOF
