// 作成者 : 板場
#include "director.hpp"
#include "platform_factory.hpp"
//#include "renderer_factory.hpp"


BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// コンストラクタ
Director::Director()
{
    platform_ = PlatformFactory::instance()->create( PlatformID::kWindows );
}

// デストラクタ
Director::~Director()
{
    platform_->finalize();
    delete platform_;
}
END_EG_EG
// EOF
