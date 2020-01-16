///
/// @file    platform_factory.hpp
/// @author  ��
///          
/// @brief   �v���b�g�t�H�[���t�@�N�g���[
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���ĉ������B<br>
///          �V�����v���b�g�t�H�[���̓o�^��REGISTER_PLATFORM�}�N�����g�p���ĉ������B<br>
///          �o�^���鐶���֐��́A�����Ɏ��s�����ꍇ�K��nullptr��ԋp����悤�ɂ��ĉ������B
///
#ifndef INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
#include <unordered_map>
#include "platform.hpp"
BEGIN_EGEG
class PlatformFactory
{
public :
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    ///
    /// @brief  �v���b�g�t�H�[���̐���
    ///
    /// @param[in] PlatformName : ��������v���b�g�t�H�[���̖��O
    /// @param[out] ppPlatform : ���������v���b�g�t�H�[�����󂯎��C���^�[�t�F�C�X
    ///
    /// @return �����ɐ���[ true ] �����Ɏ��s[ false ]
    ///
    bool create( const std::string& Platform, IPlatform** ppPlatform );

    ///
    /// @brief   �v���b�g�t�H�[���̓o�^
    /// @details ���ۂ͐��������̓o�^�ł��B
    ///
    /// @param[in] PlatformName : �֐�����������v���b�g�t�H�[���̖��O
    /// @param[in] pCreateFunction : �v���b�g�t�H�[���𐶐�����֐��̃A�h���X
    ///
    void registerPlatform( const std::string& PlatformName, IPlatform*(*pCreateFunction)() );

    PlatformFactory( const PlatformFactory& ) = delete;
    PlatformFactory& operator=( const PlatformFactory& ) = delete;
private :
    PlatformFactory() = default;
    std::unordered_map<std::string, IPlatform*(*)()> create_funcs_; /// �����������X�g
};


class REGISTER_PLATFORM
{
public :
    REGISTER_PLATFORM( const std::string& Name, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerPlatform( Name, pFunc );
    }
};
///
/// @def     REGISTER_PLATFORM
/// @brief   �v���b�g�t�H�[�����t�@�N�g���ɓo�^���܂��B
/// @details �w�b�_�[�t�@�C���ŌĂяo���Ȃ��ł��������B
///
/// @param[in] Name : �o�^����v���b�g�t�H�[���̖��O
/// @param[in] pCreateFunction : �v���b�g�t�H�[���̐������s���֐��̃A�h���X
///
#define REGISTER_PLATFORM( Name, pCreateFunction ) \
BEGIN_EGEG \
namespace impl{} namespace { namespace impl { \
REGISTER_PLATFORM register_platform( Name, pCreateFunction ); \
}} END_EGEG

END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_FACTORY_HEADER_
/// EOF
