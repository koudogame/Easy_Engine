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
BEGIN_EGEG
class Director
{
public :
    ~Director();

    ///
    /// @brief   ����������
    /// @details �K���ŏ��ɌĂяo���Ă��������B
    ///
    /// @param[in] Platform : �g�p����v���b�g�t�H�[������ID
    ///
    /// @return �������ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool initialize( PlatformID Platform );

    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static Director* instance() { static Director i; return &i; }

    ///
    /// @brief   �̗p���Ă���v���b�g�t�H�[�����擾���܂��B
    /// @details addRef�֐��̌Ăяo���͍s���Ă��܂���B
    ///
    /// @return �v���b�g�t�H�[���̃A�h���X
    ///
    IPlatform* getPlatform() const { return p_platform_; }
    ///
    /// @brief   �����_���[���擾���܂��B
    /// @details addRef�֐��̌Ăяo���͍s���Ă��܂���B
    ///
    /// @return �����_���[�̃A�h���X
    ///
    IRenderer* getRenderer() const { return p_platform_->getRenderer(); }
    ///
    /// @brief   �V�F�[�_�[���[�_�[���擾���܂��B
    /// @details addRef�֐��̌Ăяo���͍s���Ă��܂���B
    ///
    /// @return �V�F�[�_�[���[�_�[�̃A�h���X
    ///
    //IShaderLoader* getShaderLoader() const { return p_platform_->getShaderLoader(); }
    ///
    /// @brief   �e�N�X�`�����[�_�[���擾���܂��B
    /// @details addRef�֐��̌Ăяo���͍s���Ă��܂���B
    ///
    /// @return �e�N�X�`�����[�_�[�̃A�h���X 
    ///
    ITextureLoader* getTextureLoader() const { return p_platform_->getTextureLoader(); }

private :
    Director();

    IPlatform* p_platform_; /// ���������v���b�g�t�H�[�����i�[
};
END_EGEG
#endif /// !INCLUDED_EG_EG_DIRECTOR_HEADER_
/// EOF
