// 作成者 : 板場
#include "director.hpp"
#include "platform_factory.hpp"


BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// コンストラクタ
Director::Director()
{
}
// デストラクタ
Director::~Director()
{
    if( p_platform_ )
    {
        p_platform_->release();
    }
}

// 初期化処理
bool Director::initialize( PlatformID Platform )
{
    if( PlatformFactory::instance()->create(Platform, &p_platform_) == false )
        return false;

    return true;
}
END_EGEG
// EOF
