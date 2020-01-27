///
/// @file    rendering_manager.hpp
/// @author  ��
///          
/// @brief   �����_�����O�}�l�[�W���|
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
#ifndef INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
#include <deque>
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
    /// @brief  �`��Ώۉ�ʂ̃T�C�Y���擾
    ///
    /// @return �T�C�Y
    ///
    Vector2D getScreenSize() const { return p_renderer_->getScreenSize(); }

    ///
    /// @brief   �`��J�n
    /// @details �����̃J���[���́A�e�F0.0F ~ 1.0F�Őݒ肵�Ă��������B
    ///
    /// @param[in] ColorRGBA : ��ʂ̃N���A�F { R, G, B, A }
    ///
    void beginRender( const Vector4D& ColorRGBA );
    ///
    /// @brief   ���f���̕`��
    /// @details ���ۂɕ`��͍s���܂���B
    ///
    /// @param[in] Model : �`�悷�郂�f��
    ///
    void renderModel( const Model& Model );
    ///
    /// @brief   ���f���̕`��
    /// @details ���ۂɕ`��͍s���܂���B
    ///
    /// @param[in] Mesh : ���b�V��
    /// @param[in] pTexture : �e�N�X�`��
    /// @param[in] pVertexShader : ���_�V�F�[�_�[
    /// @param[in] pGeometryShader : �W�I���g���V�F�[�_�[
    /// @param[in] pPixelShader : �s�N�Z���V�F�[�_�[
    ///
    void renderModel( const Mesh& Mesh, ITexture* pTexture, IVertexShader* pVertexShader, IGeometryShader* pGeometryShader, IPixelShader* pPixelShader );
    ///
    /// @brief   �`��I��
    /// @details beginRender�̌Ăяo������A<br>
    ///          ���̊֐����Ăяo�����܂łɃG���g���[���ꂽ���f����`�悵�܂��B
    ///
    void endRender();


    ///
    /// @brief  �C���X�^���X�̐���
    ///
    /// @param[in] Creator : ������
    /// @param[in] pRenderer : �g�p���郌���_���[
    ///
    static void create( const EasyEngine& Creator, IRenderer* pRenderer );
    ///
    /// @brief  �C���X�^���X�̔j��
    ///
    /// @param[in] Deleter : �j����
    ///
    static void destroy( const EasyEngine& Deleter );

private :
    RenderingManager( IRenderer* );
    ~RenderingManager();
    RenderingManager( const RenderingManager& ) = delete;
    RenderingManager& operator=( const RenderingManager& ) = delete;

    static RenderingManager* instance_;
    IRenderer* p_renderer_;         /// �g�p���郌���_���[
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_MANAGER_HEADER_
/// EOF
