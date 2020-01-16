// �쐬�� : ��
#include "platform_factory.hpp"
#ifdef _DEBUG
#include <cassert>
#endif // !_DEBUG

BEGIN_EGEG
// PlatformFactory : �֐��̎���
/*===========================================================================*/
// �v���b�g�t�H�[���̐���
bool PlatformFactory::create( const std::string& Name, IPlatform** ppPlatform )
{
    auto find = create_funcs_.find( Name );
#ifdef _DEBUG
    assert( find != create_funcs_.end() && 
            "�o�^����Ă��Ȃ��v���b�g�t�H�[���𐶐����悤�Ƃ��܂����B" );
#endif // !_DEBUG

    *ppPlatform = find->second();
    if( *ppPlatform == nullptr ) return false;

    return true;
}

// �v���b�g�t�H�[���̓o�^
void PlatformFactory::registerPlatform( const std::string& Name, IPlatform*(*pFunc)() )
{
#ifdef _DEBUG
    auto find = create_funcs_.find( Name );
    assert( find == create_funcs_.end() &&
            "���ɓo�^�ς݂̖��O�Ńv���b�g�t�H�[����o�^���悤�Ƃ��܂����B" );
#endif // !_DEBUG

    create_funcs_.emplace( Name, pFunc );
}
END_EGEG
// EOF
