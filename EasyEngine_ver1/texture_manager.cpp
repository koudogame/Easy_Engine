// 作成者 : 板場
#include "texture_manager.hpp"


BEGIN_EGEG
TextureManager* TextureManager::instance_;

// TextureManager : 関数の実装
/*===========================================================================*/
// コンストラクタ
TextureManager::TextureManager( ITextureLoader* pLoader ) :
    p_loader_( pLoader )
{
    p_loader_->addRef();
}
// デストラクタ
TextureManager::~TextureManager()
{
    // 解放されていないテクスチャを開放する
    for( auto& texture : cache_ )
    {
        for( int i = texture.second->getRefCount(); i > 0; --i )
        {
            texture.second->release();
        }
    }

    p_loader_->release();
}

// 読み込み
bool TextureManager::load( const wchar_t* Path, ITexture** ppTexture )
{
    auto find = cache_.find( Path );
    
    // キャッシュにある場合
    if( find != cache_.end() )
    {
        find->second->addRef();
        *ppTexture = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // 読み込み
        if( p_loader_->load(Path, ppTexture) == false )
            return false;

        // キャッシュに保存
        cache_.emplace( Path, *ppTexture );
    }

    return true;
}

// 開放
void TextureManager::release( ITexture** ppTexture )
{
    // この開放で参照者がいなくなる場合
    if( (*ppTexture)->getRefCount() == 1U )
    {
        // キャッシュから削除
        for( auto itr = cache_.begin(), end = cache_.end(); itr != end; ++itr )
        {
            if( itr->second == *ppTexture )
            {
                cache_.erase( itr );
                break;
            }
        }
    }

    // 開放
    (*ppTexture)->release();
    *ppTexture = nullptr;
}

// 生成処理
void TextureManager::create( const EasyEngine* pCreator, ITextureLoader* pLoader )
{
    pCreator->proof();

    destroy( pCreator );
    instance_ = new TextureManager( pLoader );
}
// 破棄処理
void TextureManager::destroy( const EasyEngine* pDeleter )
{
    pDeleter->proof();

    if( instance_ )
    {
        delete instance_;
        instance_ = nullptr;
    }
}
END_EGEG
// EOF
