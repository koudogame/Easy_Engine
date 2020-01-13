///
/// @file    rendering_manager.hpp
/// @author  ��
///          
/// @brief   �����_�����O�}�l�[�W���\
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
#ifndef INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#define INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
#include "renderer.hpp"
BEGIN_EGEG
class RenderingManager
{
public :
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static RenderingManager* instance() { static RenderingManager i; return &i; }

    ///
    /// @brief   �`�惊�N�G�X�g��o�^
    /// @details ���̊֐��͕`����s���܂���B
    ///
    void entry( ... );

    ///
    /// @brief  �`��
    /// @detais ���̊֐����Ăяo���ꂽ���_�ł̕`�惊�N�G�X�g�����ׂĉ������܂��B
    ///
    void rendering();

private :
    RenderingManager();

    // �`�惊�N�G�X�g�X�^�b�N
};
END_EGEG
#endif /// !INCLUDED_EG_EG_RENDERING_MANAGER_HEADER_
/// EOF
