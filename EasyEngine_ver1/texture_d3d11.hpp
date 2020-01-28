///
/// @file   texture_windows.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#define INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#include <d3d11.h>
#include "texture.hpp"
BEGIN_EGEG
///
/// @class  TextureD3D11
///
/// @brief  DirectX11�p�e�N�X�`��
///
class TextureD3D11 :
    public ITexture
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pTexture : �ێ�����V�F�[�_�[���\�[�X�r���[
    ///
    TextureD3D11( ID3D11ShaderResourceView* pTexture ) :
        p_texture_( pTexture )
    {
        p_texture_->AddRef();

        /// �e�N�X�`���T�C�Y�̎擾
        ID3D11Resource* resource;
        p_texture_->GetResource( &resource );

        D3D11_TEXTURE2D_DESC tex_desc;
        static_cast<ID3D11Texture2D*>(resource)->GetDesc( &tex_desc );
        width_ = tex_desc.Width;
        height_ = tex_desc.Height;

        resource->Release();
    }

    ///
    /// @brief  �V�F�[�_�[���\�[�X�r���[�̎擾
    ///
    /// @return �ێ����Ă���V�F�[�_�[���\�[�X�r���[
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
    ID3D11ShaderResourceView* p_texture_;   /// �V�F�[�_�[���\�[�X�r���[
    long width_;
    long height_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
/// EOF
