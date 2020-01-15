///
/// @file    renderer.hpp
/// @author  ��
///          
/// @brief   �����_���[�C���^�[�t�F�C�X
///
#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
#include "interface.hpp"
#include "pixel_shader.hpp"
#include "vertex_shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"
BEGIN_EGEG
class IRenderer :
    public SharedObject
{
public :
    ///
    /// @brief  �����_�[�J�n
    ///
    /// @param[in] ClearColorRGBA : �N���A�F { R, G, B, A }
    ///
    virtual void beginRender( float ClearColorRGBA[4] ) = 0;
    ///
    /// @brief  �O���t�B�b�N�X�p�C�v���C���ɒ��_�V�F�[�_��ݒ�
    ///
    /// @param[in] pVertexShader : �ݒ肷�钸�_�V�F�[�_
    ///
    virtual void setVertexShader( IVertexShader* pVertexShader ) = 0;
    ///
    /// @brief  �O���t�B�b�N�X�p�C�v���C���Ƀs�N�Z���V�F�[�_��ݒ�
    ///
    /// @param[in] pPixelShader : �ݒ肷��s�N�Z���V�F�[�_
    ///
    virtual void setPixelShader( IPixelShader* pPixelShader ) = 0;
    ///
    /// @brief  �O���t�B�b�N�X�p�C�v���C���Ƀe�N�X�`����ݒ�
    ///
    /// @param[in] pTexture : �ݒ肷��e�N�X�`��
    ///
    virtual void setTexture( ITexture* pTexture ) = 0;
    ///
    /// @brief  ���b�V���̃����_�����O
    ///
    /// @param[in]  Object : �����_�����O���郁�b�V���f�[�^
    ///
    virtual void render( const Mesh& Object ) = 0;
    ///
    /// @brief  �����_�[�I��
    ///
    virtual void endRender() = 0;

protected :
    IRenderer() = default;
    virtual ~IRenderer() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERER_HEADER_
/// EOF
