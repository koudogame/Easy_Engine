// �쐬�� : ��
#include "shader_manager.hpp"
#include "core.hpp"

BEGIN_EGEG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
ShaderManager::ShaderManager()
{
    p_loader_ = Core::instance()->getPlatform()->getShaderLoader();
    p_loader_->addRef();
}

// ���_�V�F�[�_�\�̃��[�h
bool ShaderManager::loadVertexShader( const char* Path, IVertexShader** ppOut )
{
    auto find = vs_cache_.find( Path );

    // �L���b�V���ɂ���ꍇ
    if( find != vs_cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �ǂݍ���
        if( p_loader_->loadVertexShader(Path, ppOut) == false )
        {
            return false;
        }

        // �L���b�V���ɒǉ�
        vs_cache_.emplace( Path, *ppOut );
    }

    return true;
}

// �s�N�Z���V�F�[�_�\�̃��[�h
bool ShaderManager::loadPixelShader( const char* Path, IPixelShader** ppOut )
{
    auto find = ps_cache_.find( Path );

    // �L���b�V���ɂ���ꍇ
    if( find != ps_cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �ǂݍ���
        if( p_loader_->loadPixelShader(Path, ppOut) == false )
        {
            return false;
        }

        // �L���b�V���ɒǉ�
        ps_cache_.emplace( Path, *ppOut );
    }

    return true;
}

// ���_�V�F�[�_�[�̉��
void ShaderManager::releaseVertexShader( IVertexShader** ppShader )
{
    if( ppShader == nullptr ) return;

    // �Q�Ǝ҂̃f�N�������g�̂ݍs����ꍇ
    if( (*ppShader)->getReferencedNum() > 1U )
    {
        (*ppShader)->release();
    }
    // ���ۂɊJ���������s����ꍇ
    else
    {
        // �L���b�V������폜
        for( auto itr = vs_cache_.begin(), end = vs_cache_.end();
            itr != end; ++itr )
        {
            if( itr->second == *ppShader )
            {
                vs_cache_.erase( itr );
                break;
            }
        }

        // ���
        (*ppShader)->release();
    }
}

// �s�N�Z���V�F�[�_�̉��
void ShaderManager::releasePixelShader( IPixelShader** ppShader )
{
    if( ppShader == nullptr ) return;

    // �Q�Ǝ҂̃f�N�������g�̂ݍs����ꍇ
    if( (*ppShader)->getReferencedNum() > 1U )
    {
        (*ppShader)->release();
    }
    // ���ۂɊJ���������s����ꍇ
    else
    {
        // �L���b�V������폜
        for( auto itr = ps_cache_.begin(), end = ps_cache_.end();
            itr != end; ++itr )
        {
            if( itr->second == *ppShader )
            {
                ps_cache_.erase( itr );
                break;
            }
        }

        // ���
        (*ppShader)->release();
    }
}
END_EGEG
// EOF
