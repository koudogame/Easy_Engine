// �쐬�� : ��
#include "texture_manager.hpp"
#include "core.hpp"

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
TextureManager::TextureManager()
{
    p_loader_ = Core::instance()->getPlatform()->getTextureLoader();
    p_loader_->addRef();
}

// �e�N�X�`���̓ǂݍ���
bool TextureManager::load( const wchar_t* Path, ITexture** ppOut )
{
    auto find = cache_.find( Path );

    // �L���b�V���ɂ���ꍇ
    if( find != cache_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �ǂݍ���
        if( p_loader_->load(Path, ppOut) == false )
        {
            return false;
        }

        // �L���b�V���ɒǉ�
        cache_.emplace( Path, *ppOut );
    }

    return true;
}

// �e�N�X�`�����
void TextureManager::release( ITexture** ppTexture )
{
    if( ppTexture == nullptr ) return;

    // �Q�Ɛ��̃f�N�������g�̂ݍs����ꍇ
    if( (*ppTexture)->getReferencedNum() > 1U )
    {
        (*ppTexture)->release();
    }
    // ���ۂɊJ���������s����ꍇ
    else
    {
        // �L���b�V������폜
        for( auto itr = cache_.begin(), end = cache_.end();
            itr != end; ++itr )
        {
                if( itr->second == *ppTexture )
                {
                    cache_.erase( itr );
                    break;
                }
        }

        // ���
        (*ppTexture)->release();
    }
}
END_EG_EG
// EOF
