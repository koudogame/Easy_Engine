///
/// @file    core.hpp
/// @author  ��
///          
/// @brief   ���j�N���X
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B
///
#ifndef INCLUDED_EG_EG_CORE_HEADER_
#define INCLUDED_EG_EG_CORE_HEADER_
#include "easy_engine.hpp"
#include "platform.hpp"
BEGIN_EG_EG
class Core
{
public :
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static Core* instance() { static Core i; return &i; }

    ///
    /// @brief  �v���b�g�t�H�[�����擾���܂��B
    ///
    /// @return �v���b�g�t�H�[���̃A�h���X
    ///
    IPlatform* getPlatform() const { return p_platform_; }

    ///
    /// @brief   ����������
    ///
    /// @param[in] Platform : �^�[�Q�b�g�v���b�g�t�H�[��
    ///
    /// @return �������ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool initialize( PlatformID TargetPlatform );

    ///
    /// @brief  �I������
    ///
    void finalize();

private :
    Core() = default;

    IPlatform* p_platform_ = nullptr;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_CORE_HEADER_
/// EOF
