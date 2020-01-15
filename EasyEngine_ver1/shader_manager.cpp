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

    p_loader_->release();
}

// ���_�V�F�[�_�̓ǂݍ���
bool ShaderManager::loadVertexShader( const char* Path, IVertexShader** ppShader )
{
    // �ǂݍ���
    if( p_loader_->loadVertexShader(Path, ppShader) == false )
        return false;

    // ���X�g�ɕێ�����
    vs_list_.emplace( *ppShader );

    return true;
}
// ���_�V�F�[�_�̉��
void ShaderManager::releaseVertexShader( IVertexShader** ppShader )
{
    // ���X�g�ɑ��݂���V�F�[�_�[�̂݉���̑ΏۂƂ���
    auto find = vs_list_.find( *ppShader );
    if( find != vs_list_.end() )
    {
        // ���̉���Ŏ��ۂɊJ�������ꍇ�A���X�g����폜
        if( (*ppShader)->getRefCount() == 1U )
        {
            vs_list_.erase( find );
        }

        // ���
        (*ppShader)->release();
    }
}

// �W�I���g���V�F�[�_�\�̓ǂݍ���
bool ShaderManager::loadGeometryShader( const char* Path, IGeometryShader** ppShader )
{
    // �ǂݍ���
    if( p_loader_->loadGeometryShader(Path, ppShader) == false )
        return false;

    // ���X�g�ɕێ�����
    gs_list_.emplace( *ppShader );

    return true;
}
// �W�I���g���V�F�[�_�[�̉��
void ShaderManager::releaseGeometryShader( IGeometryShader** ppShader )
{
    // ���X�g�ɑ��݂���V�F�[�_�[�̂ݑΏۂƂ���
    auto find = gs_list_.find( *ppShader );
    if( find != gs_list_.end() )
    {
        // ���̉���Ŏ��ۂɊJ�������ꍇ�A���X�g����폜
        if( (*ppShader)->getRefCount() == 1U )
        {
            gs_list_.erase( find );
        }

        // ���
        (*ppShader)->release();
    }
}

// �s�N�Z���V�F�[�_�\�̓ǂݍ���
bool ShaderManager::loadPixelShader( const char* Path, IPixelShader** ppShader )
{
    // �ǂݍ���
    if( p_loader_->loadPixelShader(Path, ppShader) == false )
        return false;

    // ���X�g�ɕێ�����
    ps_list_.emplace( *ppShader );

    return true;
}
// �s�N�Z���V�F�[�_�\�̉��
void ShaderManager::releasePixelShader( IPixelShader** ppShader )
{
    // ���X�g�̑��݂���V�F�[�_�[�̂ݑΏۂƂ���
    auto find = ps_list_.find( *ppShader );
    if( find != ps_list_.end() )
    {
        // �̉���Ŏ��ۂɊJ�������ꍇ�A���X�g����폜
        if( (*ppShader)->getRefCount() == 1U )
        {
            ps_list_.erase( find );
        }

        // ���
        (*ppShader)->release();
    }
}

// ��������
void ShaderManager::create( const EasyEngine* pCreator, IShaderLoader* pLoader )
{
    pCreator->proof();

    destroy( pCreator );
    instance_ = new ShaderManager( pLoader );
}
// �j������
void ShaderManager::destroy( const EasyEngine* pDeleter )
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
