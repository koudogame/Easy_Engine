// �쐬�� : ��
#include "shader_manager.hpp"

BEGIN_EGEG
ShaderManager* ShaderManager::instance_;

// ShaderManager : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
ShaderManager::ShaderManager( IShaderLoader *pLoader ) :
    p_loader_( pLoader )
{
    p_loader_->addRef();
}
// �f�X�g���N�^
ShaderManager::~ShaderManager()
{
    // �J������Ă��Ȃ��V�F�[�_�[���J������
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
