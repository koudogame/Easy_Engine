///
/// @file    renderer.hpp
/// @author  ��
///          
/// @brief   �����_���[�C���^�[�t�F�C�X
/// @details RendererFactory�ɂ��񋟂���܂��B<br>
///          �V���������_���[���쐬����ہARendererFactory�ւ̓o�^��K���s���ĉ������B<br>
///          �o�^�̍ۂ�ID���ꏏ�ɓo�^���邽�߁ARendererID�Ɏ���ID��ǉ����ĉ������B
///
#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
#include "interface.hpp"
#include "vertex_shader.hpp"
#include "pixel_shader.hpp"
#include "texture.hpp"
#include "mesh.hpp"
BEGIN_EG_EG
///
/// @enum  RendererID
/// @brief �����_���[�����ʂ���ID�Q�ł��B
///
enum RendererID
{
    kDirect3D11,
};

class IRenderer :
    public Interface
{
public :
// FileIO
/*-----------------------------------------------------------------*/
    ///
    /// @brief  �e�N�X�`���̃��[�h
    ///
    /// @param[in]  FilePath : �ǂݍ��މ摜�̃t�@�C���p�X
    /// @param[out] ppOutTexture : ���������e�N�X�`�����󂯎��C���^�[�t�F�C�X�̃A�h���X
    ///
    /// @return �����ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool loadTexture( const wchar_t FilePath[], ITexture** ppOutTexture ) = 0;
    ///
    /// @brief  ���_�V�F�[�_�̃��[�h
    ///
    /// @param[in]  FilePath : �R���p�C���ςݒ��_�V�F�[�_�̃t�@�C���p�X
    /// @param[out] ppOutShader : ���������V�F�[�_�[���󂯎��C���^�[�t�F�C�X�̃A�h���X
    ///
    /// @return �����ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool loadVertexShader( const char FilePath[], IVertexShader** ppOutShader ) = 0;
    ///
    /// @brief  �s�N�Z���V�F�[�_�̃��[�h
    ///
    /// @param[in]  FilePath : �R���p�C���ς݃s�N�Z���V�F�[�_�̃t�@�C���p�X
    /// @param[out] ppOutshader : ���������V�F�[�_�[���󂯎��C���^�[�t�F�C�X�̃A�h���X
    ///
    /// @return �����ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    virtual bool loadPixelShader( const char FilePath[], IPixelShader** ppOutShader ) = 0;
    
// Render
/*-----------------------------------------------------------------*/
    ///
    /// @brief  �����_�[�J�n
    ///
    /// @param[in] BackColorRGBA : �N���A�F { R, G, B, A }
    ///
    virtual void beginRender( float BackColorRGBA[4] ) = 0;
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
END_EG_EG
#endif ///INCLUDED_EG_EG_RENDERER_HEADER_
/// EOF
