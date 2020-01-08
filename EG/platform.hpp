///
/// @file    platform.hpp
/// @author  ��
///          
/// @brief   �v���b�g�t�H�[���C���^�[�t�F�C�X
/// @details PlatformFactory�ɂ��񋟂���܂��B<br>
///          �V�����v���b�g�t�H�[�����쐬����ہAPlatformFactory�ւ̓o�^��K���s���Ă��������B<br>
///          �o�^���Ɏ���ID���g�p����̂ŁAPlatformID�Ɏ���ID��ǉ����Ă��������B
///
#ifndef INCLUDED_EG_EG_PLATFORM_HEADER_
#define INCLUDED_EG_EG_PLATFORM_HEADER_
#include <functional>
#include "interface.hpp"
BEGIN_EG_EG
///
/// @enum   PlatformID
/// @brief  �v���b�g�t�H�[�������ʂ���ID�ł��B
///
enum PlatformID
{
    kWindows,
    kNintendoSwitch,
};

class IPlatform :
    public Interface
{
public :
    ///
    /// @brief   �Q�[�����[�v
    /// @details �����̊֐��ɂ���<br>
    ///          �����ɂ͌Ăяo�����̌o�ߎ���(: �~���b)��^���܂��B<br>
    ///          �߂�l��[ false ]���Ԃ��Ă����ꍇ�A���[�v���I�����܂��B
    ///
    /// @param[in]  pUpdateFunc : �����[�v�Ăяo���֐��ւ̃|�C���^
    ///
    virtual void gameLoop( std::function<bool(long long)> pUpdateFunc ) = 0;

    ///
    /// @brief  �_�C�A���O�{�b�N�X�̕\��
    ///
    /// @param[in]  Message : �_�C�A���O�{�b�N�X�ɕ\�����镶����
    ///
    virtual void showDialogBox( const char Message[] ) = 0;

protected :
    IPlatform() = default;
    virtual ~IPlatform() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_PLATFORM_HEADER_
/// EOF
