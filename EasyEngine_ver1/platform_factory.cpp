// 作成者 : 板場
#include "platform_factory.hpp"
#ifdef _DEBUG
#include <cassert>
#endif // !_DEBUG

BEGIN_EGEG
// PlatformFactory : 関数の実装
/*===========================================================================*/
// プラットフォームの生成
bool PlatformFactory::create( const std::string& Name, IPlatform** ppPlatform )
{
    auto find = create_funcs_.find( Name );
#ifdef _DEBUG
    assert( find != create_funcs_.end() && 
            "登録されていないプラットフォームを生成しようとしました。" );
#endif // !_DEBUG

    *ppPlatform = find->second();
    if( *ppPlatform == nullptr ) return false;

    return true;
}

// プラットフォームの登録
void PlatformFactory::registerPlatform( const std::string& Name, IPlatform*(*pFunc)() )
{
#ifdef _DEBUG
    auto find = create_funcs_.find( Name );
    assert( find == create_funcs_.end() &&
            "既に登録済みの名前でプラットフォームを登録しようとしました。" );
#endif // !_DEBUG

    create_funcs_.emplace( Name, pFunc );
}
END_EGEG
// EOF
