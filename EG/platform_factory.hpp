///
/// @file    platform_factory.hpp
/// @author  ��
///          
/// @brief   �v���b�g�t�H�[���t�@�N�g��
/// @details �V���O���g���N���X�ł��B�A�N�Z�X�ɂ�instance�֐����g�p���Ă��������B
///
#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#include <unordered_map>
#include "platform.hpp"

///
/// @def     ADD_PLATFORM
/// @brief   �v���b�g�t�H�[���̓o�^����
/// @details �w�b�_�[�t�@�C���ŌĂяo���Ȃ��ł��������B
///
/// @param[in] ID : �o�^����v���b�g�t�H�[������ID
/// @param[in] pCreateFunction : �������������������֐��̃A�h���X
///
#define ADD_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddPlatform add_platform( ID, pCreateFunction ); \
}} END_EG_EG

BEGIN_EG_EG
class PlatformFactory
{
public :
    ///
    /// @brief  �C���X�^���X���擾���܂��B
    ///
    /// @return �C���X�^���X�̃A�h���X
    ///
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    ///
    /// @brief  �v���b�g�t�H�[���̓o�^
    ///
    /// @param[in] ID : �v���b�g�t�H�[������ID
    /// @param[in] pCreateFunction : �v���b�g�t�H�[�������֐��ւ̃|�C���^
    ///
    void registerPlatform( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    ///
    /// @brief  �v���b�g�t�H�[���̐���
    ///
    /// @param[in] ID : ��������v���b�g�t�H�[���̎���ID
    /// @param[out] ppOutPlatform : ���������v���b�g�t�H�[�����󂯎��C���^�[�t�F�C�X�̃A�h���X
    ///
    /// @return �����ɐ��������ꍇ[ true ] ���s�����ꍇ[ false ]��ԋp���܂��B
    ///
    bool create( PlatformID ID, IPlatform** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        if( *pOutPtr == nullptr ) return false;

        return true;
    }

private :
    PlatformFactory() = default;
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_; /// �v���b�g�t�H�[�����������֐��̃A�h���X�Q
};

class AddPlatform
{
public :
    AddPlatform( PlatformID ID, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerPlatform(ID, pFunc);
    }
};
END_EG_EG
#endif /// INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
/// EOF
