// 作成者 : 板場
#include "system_manager.hpp"

BEGIN_EGEG
SystemManager* SystemManager::instance_;

// SystemManager : 関数の実装
/*===========================================================================*/
// コンストラクタ
SystemManager::SystemManager( IPlatform* pPlatform ) :
    p_platform_( pPlatform )
{
}
// デストラクタ
SystemManager::~SystemManager()
{
    delete p_platform_;
}

// ダイアログボックスの表示
void SystemManager::showDialogBox( const std::string& Message )
{
    p_platform_->showDialogBox( Message );
}

// インスタンスの生成
void SystemManager::create( const EasyEngine& Creator, IPlatform* pPlatform )
{
    destroy( Creator );
    instance_ = new SystemManager( pPlatform );
}

// インスタンスの破棄
void SystemManager::destroy( const EasyEngine& Deleter )
{
    Deleter.proof();

    if( instance_ )
    {
        delete instance_;
        instance_ = nullptr;
    }
}
END_EGEG
// EOF
