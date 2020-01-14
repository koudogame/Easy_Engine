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
    p_loader_->addRef();
}
// デストラクタ
ShaderManager::~ShaderManager()
{
    // 開放されていないシェーダーを開放する
    auto forcedRelease = []( Interface* I )
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

    p_loader_->release();
}
END_EGEG
// EOF
