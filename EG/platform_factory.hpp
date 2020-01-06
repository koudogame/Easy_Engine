#ifndef INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
#define INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// �쐬�� : ��
#include <unordered_map>
#include "platform.hpp"

// �v���b�g�t�H�[���̒ǉ�
#define ADD_PLATFORM( ID, pCreateFunction ) \
BEGIN_EG_EG \
namespace impl{} namespace { namespace impl { \
AddPlatform add_platform( ID, pCreateFunction ); \
}} END_EG_EG


BEGIN_EG_EG
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
    // �v���b�g�t�H�[���̓o�^
    //
    // in ID : �v���b�g�t�H�[��ID
    // in pCreateFunction : �������������������֐��ւ̃|�C���^
    //
    void registerPlatform( PlatformID ID, IPlatform*(*pCreateFunction)() )
    {
        functions_[ID] = pCreateFunction;
    }

    //
    // �v���b�g�t�H�[���̐���
    // 
    // in ID : ��������v���b�g�t�H�[����ID
    // in pOutPtr : ���������I�u�W�F�N�g�ւ̃|�C���^���i�[����ϐ��̃A�h���X
    //
    // out true  : ��������
    // out false : �������s
    //
    bool create( PlatformID ID, IPlatform** pOutPtr )
    {
        auto function = functions_.find(ID);
        if( function == functions_.end() ) return false;

        *pOutPtr = function->second();
        return true;
    }

private :
    PlatformFactory() = default;
    std::unordered_map<PlatformID, IPlatform*(*)()> functions_;
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
#endif // INCLUDED_EG_EG_PLATFORM_FACTORY_HEADER_
// EOF
