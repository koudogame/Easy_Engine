// 作成者 : 板場
#include "texture_loader.hpp"
#include "texture.hpp"

BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// テクスチャのロード
bool ITextureLoader::load( const wchar_t* FilePath, ITexture** ppOut )
{
    auto find = cache_.find( FilePath );
    if( find != cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    else
    {
        ITexture* loaded;
        if( loadFromFile( FilePath, &loaded ) == false )
            return false;

        cache_.emplace( FilePath, loaded );
        *ppOut = loaded;
    }

    return true;
}

// 解放の通知
void ITextureLoader::notifyReleaseTexture( ITexture* Notifier )
{
    for( auto itr = cache_.begin(), end = cache_.end(); itr != end; ++itr )
    {
        if( itr->second == Notifier )
        {
            cache_.erase( itr );
            return;
        }
    }
}
END_EGEG
// EOF
