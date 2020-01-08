///
/// @file    director.hpp
/// @author  ��
///          
/// @brief   �Q�[���S�̓����N���X
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
#ifndef INCLUDED_EG_EG_DIRECTOR_HEADER_
#define INCLUDED_EG_EG_DIRECTOR_HEADER_
#include "platform.hpp"
#include "renderer.hpp"
BEGIN_EG_EG
class Director
{
public :
    ~Director();

    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static Director* instance() { static Director i; return &i; }

    ///
    /// @brief  �̗p���Ă���v���b�g�t�H�[�����擾���܂��B
    ///
    /// @return �C���^�[�t�F�C�X
    ///
    IPlatform* getPlatform() const { return p_platform_; }
    ///
    /// @brief  �̗p���Ă��郌���_���[���擾���܂��B
    ///
    /// @return �C���^�[�t�F�C�X
    ///
    IRenderer* getRenderer() const { return p_renderer_; }

    ///
    /// @brief   ����������
    /// @details �K���ŏ��ɌĂяo���Ă��������B
    ///
    /// @param[in] Platform : �g�p����v���b�g�t�H�[������ID
    /// @param[in] Renderer : �g�p���郌���_���[����ID
    ///
    /// @return �������ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool initialize( PlatformID Platform, RendererID Renderer );

private :
    Director();

    IPlatform* p_platform_; /// ���������v���b�g�t�H�[�����i�[
    IRenderer* p_renderer_; /// �������������_���[���i�[
};
END_EG_EG
#endif /// INCLUDED_EG_EG_DIRECTOR_HEADER_
/// EOF
