///
/// @file   texture_windows.hpp
/// @author ��
///
/// @brief  Windows�p�e�N�X�`��
///
#ifndef INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#define INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
#include <d3d11.h>
#include "texture.hpp"
BEGIN_EGEG
class TextureWindows :
    public ITexture
{
public :
    ///
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pTexture : �ێ�����V�F�[�_�[���\�[�X�r���[
    ///
    TextureWindows( ID3D11ShaderResourceView* pTexture ) :
        p_texture_( pTexture )
    {
        p_texture_->AddRef();
    }

    ///
    /// @brief  �V�F�[�_�[���\�[�X�r���[�̎擾
    ///
    /// @return �ێ����Ă���V�F�[�_�[���\�[�X�r���[
    ///
    ID3D11ShaderResourceView* getShaderResourceView() const { p_texture_->AddRef(); return p_texture_; }

private :
    ~TextureWindows()
    {
        p_texture_->Release();
    }
    ID3D11ShaderResourceView* p_texture_;   /// �V�F�[�_�[���\�[�X�r���[
};
END_EGEG
#endif /// !INCLUDED_EGEG_TEXTURE_WINDOWS_HEADER_
/// EOF
