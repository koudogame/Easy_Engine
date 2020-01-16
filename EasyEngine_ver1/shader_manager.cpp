// 作成者 : 板場
#include "shader_manager.hpp"

BEGIN_EGEG
ShaderManager* ShaderManager::instance_;

// ShaderManager : 関数の実装
/*===========================================================================*/
// コンストラクタ
ShaderManager::ShaderManager( IShaderLoader *pLoader ) :
    p_loader_( pLoader )
{
}
// デストラクタ
ShaderManager::~ShaderManager()
{
    // 開放されていないシェーダーを開放する
    auto forcedRelease = []( SharedObject* I )
    {
        for( int i = I->getRefCount(); i > 0; --i )
        {
            I->release();
        }
    };
    for( auto& vs : vs_list_ )
    {
        forcedRelease( vs );
    }
    for( auto& gs : gs_list_ )
    {
        forcedRelease( gs );
    }
    for( auto& ps : ps_list_ )
    {
        forcedRelease( ps );
    }

    delete p_loader_;
}

// 頂点シェーダの読み込み
bool ShaderManager::loadVertexShader( const std::string& Path, IVertexShader** ppShader )
{
    // 読み込み
    if( p_loader_->loadVertexShader(Path, ppShader) == false )
        return false;

    // リストに保持する
    vs_list_.emplace( *ppShader );

    return true;
}
// 頂点シェーダの解放
void ShaderManager::releaseVertexShader( IVertexShader** ppShader )
{
    // リストに存在するシェーダーのみ解放の対象とする
    auto find = vs_list_.find( *ppShader );
    if( find != vs_list_.end() )
    {
        // この解放で実際に開放される場合、リストから削除
        if( (*ppShader)->getRefCount() == 1U )
        {
            vs_list_.erase( find );
        }

        // 解放
        (*ppShader)->release();
    }
}

// ジオメトリシェーダ―の読み込み
bool ShaderManager::loadGeometryShader( const std::string& Path, IGeometryShader** ppShader )
{
    // 読み込み
    if( p_loader_->loadGeometryShader(Path, ppShader) == false )
        return false;

    // リストに保持する
    gs_list_.emplace( *ppShader );

    return true;
}
// ジオメトリシェーダーの解放
void ShaderManager::releaseGeometryShader( IGeometryShader** ppShader )
{
    // リストに存在するシェーダーのみ対象とする
    auto find = gs_list_.find( *ppShader );
    if( find != gs_list_.end() )
    {
        // この解放で実際に開放される場合、リストから削除
        if( (*ppShader)->getRefCount() == 1U )
        {
            gs_list_.erase( find );
        }

        // 解放
        (*ppShader)->release();
    }
}

// ピクセルシェーダ―の読み込み
bool ShaderManager::loadPixelShader( const std::string& Path, IPixelShader** ppShader )
{
    // 読み込み
    if( p_loader_->loadPixelShader(Path, ppShader) == false )
        return false;

    // リストに保持する
    ps_list_.emplace( *ppShader );

    return true;
}
// ピクセルシェーダ―の解放
void ShaderManager::releasePixelShader( IPixelShader** ppShader )
{
    // リストの存在するシェーダーのみ対象とする
    auto find = ps_list_.find( *ppShader );
    if( find != ps_list_.end() )
    {
        // 個の解放で実際に開放される場合、リストから削除
        if( (*ppShader)->getRefCount() == 1U )
        {
            ps_list_.erase( find );
        }

        // 解放
        (*ppShader)->release();
    }
}

// 生成処理
void ShaderManager::create( const EasyEngine& Creator, IShaderLoader* pLoader )
{
    destroy( Creator );
    instance_ = new ShaderManager( pLoader );
}
// 破棄処理
void ShaderManager::destroy( const EasyEngine& Deleter )
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
