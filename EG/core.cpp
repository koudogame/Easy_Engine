// 作成者 : 板場
#include "core.hpp"
#include "platform_factory.hpp"

BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// 初期化処理
bool Core::initialize( PlatformID Platform )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    return true;
}
// 終了処理
void Core::finalize()
{
    if( p_platform_ ) p_platform_->release();
}
END_EGEG
// EOF
