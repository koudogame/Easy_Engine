#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// �쐬�� : ��
#include <unordered_map>
#include "platform.hpp"

#define ADD_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddPlatform add_platform( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
enum PlatformID
{
    kWindows,
    kNintendoSwitch,
};
//
// �v���b�g�t�H�[���p�t�@�N�g��
// �V���O���g���N���X�ł��B�A�N�Z�X�ɂ� instance�֐����g�p���ĉ������B
//
class PlatformFactory
{
public :
    // �C���X�^���X�ւ̃A�N�Z�X
    static PlatformFactory* instance() { static PlatformFactory i; return &i; }

    //
    // �v���b�g�t�H�[���̒ǉ�
    //
    // in ID : �v���b�g�t�H�[��ID
    // in pCreateFunction : �������������������֐��ւ̃|�C���^
    //
    void registerCreateFunction( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    //
    // �v���b�g�t�H�[���̐���
    //
    IPlatform* create( PlatformID ID )
    {
        auto function = functions_.find(ID);
        return function->second();
    }

private :
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_;
};

class AddPlatform
{
public :
    AddPlatform( PlatformID ID, IPlatform*(*pFunc)() )
    {
        PlatformFactory::instance()->registerCreateFunction(ID, pFunc);
    }
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// EOF
