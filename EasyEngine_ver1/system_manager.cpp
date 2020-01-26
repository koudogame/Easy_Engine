// 作成者 : 板場
#include "system_manager.hpp"

BEGIN_EGEG
SystemManager* SystemManager::instance_;

// SystemManager
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

// メインループ
void SystemManager::mainLoop( std::function<bool(uint64_t)> pFunc )
{
    p_platform_->mainLoop( pFunc );
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
