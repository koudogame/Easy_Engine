// 作成者 : 板場
#include "sound_manager.hpp"

BEGIN_EGEG
SoundManager* SoundManager::instance_;

// SoundManager
/*===========================================================================*/
// コンストラクタ
SoundManager::SoundManager( ISoundLoader* pLoader ) :
    p_loader_( pLoader )
{
}
// デストラクタ
SoundManager::~SoundManager()
{
    delete p_loader_;
}

// インスタンスの生成
void SoundManager::create( const EasyEngine& Creator, ISoundLoader* pLoader )
{
    destroy( Creator );

    instance_ = new SoundManager( pLoader );
}
// インスタンスの破棄
void SoundManager::destroy( const EasyEngine& Deleter )
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
