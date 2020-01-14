///
/// @file    rendering_manager.hpp
/// @author  ��
///          
/// @brief   �����_�����O�}�l�[�W���|
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#include "easy_engine.hpp"
#include "renderer.hpp"
BEGIN_EGEG
class RenderingManager
{
public :
    ///
    /// @brief  �C���X�^���X�ւ̃A�N�Z�X
    ///
    /// @return �C���X�^���X
    ///
    static RenderingManager* instance() { return instance_; }

    ///
    /// @brief   �`��J�n
    /// @details �����̃J���[���́A�e�F0.0F ~ 1.0F�Őݒ肵�Ă��������B
    ///
    /// @param[in] ColorRGBA : ��ʂ̃N���A�F { R, G, B, A }
    ///
    void beginRender( const Vector4D& Color );
    ///
    /// @brief   �`��̃G���g���[
    /// @details ���ۂɕ`��͍s���܂���B
    ///
    /// @param[in] Model : �`�悷�郂�f��
    ///
    void entryRender( const Model& Model );
    ///
    /// @brief   �`��̃G���g���[
    /// @details ���ۂɕ`��͍s���܂���B
    ///
    /// @param[in] Mesh : ���b�V��
    /// @param[in] pTexture : �e�N�X�`��
    /// @param[in] pVertexShader : ���_�V�F�[�_�[
    /// @param[in] pGeometryShader : �W�I���g���V�F�[�_�[
    /// @param[in] pPixelShader : �s�N�Z���V�F�[�_�[
    ///
    void entryRender( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader );
    ///
    /// @brief   �`��I��
    /// @details beginRender�̌Ăяo������A<br>
    ///          ���̊֐����Ăяo�����܂łɃG���g���[���ꂽ���f����`�悵�܂��B
    ///
    void endRender();


    ///
    /// @brief  �C���X�^���X�̐���
    ///
    /// @param[in] pCreator : ������
    /// @param[in] pRenderer : �g�p���郌���_���[
    ///
    static void create( EasyEngine* pCreator, IRenderer* pRenderer );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] pDeleter : �j����
    ///
    static void destroy( EasyEngine* pDeleter );
    ~RenderingManager();

    RenderingManager( const RenderingManager& ) = delete;
    RenderingManager& operator=( const RenderingManager& ) = delete;
private :
    RenderingManager( IRenderer* );
    static RenderingManager* instance_;
    IRenderer* p_renderer_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
/// EOF