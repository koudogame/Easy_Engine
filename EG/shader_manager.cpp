// 作成者 : 板場
#include "shader_manager.hpp"
#include "core.hpp"

BEGIN_EGEG
// 関数の実装
/*===========================================================================*/
// コンストラクタ
ShaderManager::ShaderManager()
{
    p_loader_ = Core::instance()->getPlatform()->getShaderLoader();
    p_loader_->addRef();
}

// 頂点シェーダ―のロード
bool ShaderManager::loadVertexShader( const char* Path, IVertexShader** ppOut )
{
    auto find = vs_cache_.find( Path );

    // キャッシュにある場合
    if( find != vs_cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // 読み込み
        if( p_loader_->loadVertexShader(Path, ppOut) == false )
        {
            return false;
        }

        // キャッシュに追加
        vs_cache_.emplace( Path, *ppOut );
    }

    return true;
}

// ピクセルシェーダ―のロード
bool ShaderManager::loadPixelShader( const char* Path, IPixelShader** ppOut )
{
    auto find = ps_cache_.find( Path );

    // キャッシュにある場合
    if( find != ps_cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // 読み込み
        if( p_loader_->loadPixelShader(Path, ppOut) == false )
        {
            return false;
        }

        // キャッシュに追加
        ps_cache_.emplace( Path, *ppOut );
    }

    return true;
}

// 頂点シェーダーの解放
void ShaderManager::releaseVertexShader( IVertexShader** ppShader )
{
    if( ppShader == nullptr ) return;

    // 参照者のデクリメントのみ行われる場合
    if( (*ppShader)->getReferencedNum() > 1U )
    {
        (*ppShader)->release();
    }
    // 実際に開放処理が行われる場合
    else
    {
        // キャッシュから削除
        for( auto itr = vs_cache_.begin(), end = vs_cache_.end();
            itr != end; ++itr )
        {
            if( itr->second == *ppShader )
            {
                vs_cache_.erase( itr );
                break;
            }
        }

        // 解放
        (*ppShader)->release();
    }
}

// ピクセルシェーダの解放
void ShaderManager::releasePixelShader( IPixelShader** ppShader )
{
    if( ppShader == nullptr ) return;

    // 参照者のデクリメントのみ行われる場合
    if( (*ppShader)->getReferencedNum() > 1U )
    {
        (*ppShader)->release();
    }
    // 実際に開放処理が行われる場合
    else
    {
        // キャッシュから削除
        for( auto itr = ps_cache_.begin(), end = ps_cache_.end();
            itr != end; ++itr )
        {
            if( itr->second == *ppShader )
            {
                ps_cache_.erase( itr );
                break;
            }
        }

        // 解放
        (*ppShader)->release();
    }
}
END_EGEG
// EOF
