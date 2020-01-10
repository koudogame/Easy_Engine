///
/// @file   texture_d3d11.hpp
/// @author ��
///
/// @brief  D3D11�p�e�N�X�`��
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
    /// @brief  �R���X�g���N�^
    ///
    /// @param[in] pManager : ���g�̊Ǘ���
    /// @param[in] pView : �ێ�����V�F�[�_�[���\�[�X�r���[
    ///
    TextureD3D11( TextureLoaderD3D11* pManager, ID3D11ShaderResourceView* pView ) :
        p_manager_(pManager),
        p_view_(pView)
    {
        p_view_->AddRef();
    }

    ///
    /// @brief  �ێ����Ă��郊�\�[�X���擾���܂��B
    ///
    /// @return �ێ����Ă��郊�\�[�X�̃A�h���X
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
