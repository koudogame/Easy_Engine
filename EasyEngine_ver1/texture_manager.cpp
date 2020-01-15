// �쐬�� : ��
#include "texture_manager.hpp"


BEGIN_EGEG
TextureManager* TextureManager::instance_;

// TextureManager : �֐��̎���
/*===========================================================================*/
// �R���X�g���N�^
TextureManager::TextureManager( ITextureLoader* pLoader ) :
    p_loader_( pLoader )
{
    p_loader_->addRef();
}
// �f�X�g���N�^
TextureManager::~TextureManager()
{
    // �������Ă��Ȃ��e�N�X�`�����J������
    for( auto& texture : cache_ )
    {
        for( int i = texture.second->getRefCount(); i > 0; --i )
        {
            texture.second->release();
        }
    }

    p_loader_->release();
}

// �ǂݍ���
bool TextureManager::load( const wchar_t* Path, ITexture** ppTexture )
{
    auto find = cache_.find( Path );
    
    // �L���b�V���ɂ���ꍇ
    if( find != cache_.end() )
    {
        find->second->addRef();
        *ppTexture = find->second;
    }
    // �V�K�ɓǂݍ��ޏꍇ
    else
    {
        // �ǂݍ���
        if( p_loader_->load(Path, ppTexture) == false )
            return false;

        // �L���b�V���ɕۑ�
        cache_.emplace( Path, *ppTexture );
    }

    return true;
}

// �J��
void TextureManager::release( ITexture** ppTexture )
{
    // ���̊J���ŎQ�Ǝ҂����Ȃ��Ȃ�ꍇ
    if( (*ppTexture)->getRefCount() == 1U )
    {
        // �L���b�V������폜
        for( auto itr = cache_.begin(), end = cache_.end(); itr != end; ++itr )
        {
            if( itr->second == *ppTexture )
            {
                cache_.erase( itr );
                break;
            }
        }
    }

    // �J��
    (*ppTexture)->release();
    *ppTexture = nullptr;
}

// ��������
void TextureManager::create( const EasyEngine* pCreator, ITextureLoader* pLoader )
{
    pCreator->proof();

    destroy( pCreator );
    instance_ = new TextureManager( pLoader );
}
// �j������
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
