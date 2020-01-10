// 作成者 : 板場
#include "texture_manager.hpp"
#include "core.hpp"

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// コンストラクタ
TextureManager::TextureManager()
{
    p_loader_ = Core::instance()->getPlatform()->getTextureLoader();
    p_loader_->addRef();
}

// テクスチャの読み込み
bool TextureManager::load( const wchar_t* Path, ITexture** ppOut )
{
    auto find = cache_.find( Path );

    // キャッシュにある場合
    if( find != cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // 読み込み
        if( p_loader_->load(Path, ppOut) == false )
        {
            return false;
        }

        // キャッシュに追加
        cache_.emplace( Path, *ppOut );
    }

    return true;
}

// テクスチャ解放
void TextureManager::release( ITexture** ppTexture )
{
    if( ppTexture == nullptr ) return;

    // 参照数のデクリメントのみ行われる場合
    if( (*ppTexture)->getReferencedNum() > 1U )
    {
        (*ppTexture)->release();
    }
    // 実際に開放処理が行われる場合
    else
    {
        // キャッシュから削除
        for( auto itr = cache_.begin(), end = cache_.end();
            itr != end; ++itr )
        {
                if( itr->second == *ppTexture )
                {
                    cache_.erase( itr );
                    break;
                }
        }

        // 解放
        (*ppTexture)->release();
    }
}
END_EG_EG
// EOF
