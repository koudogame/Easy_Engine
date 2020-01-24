// �쐬�� : ��
#include "texture_manager.hpp"


BEGIN_EGEG
TextureManager* TextureManager::instance_;

// TextureManager
/*===========================================================================*/
// �R���X�g���N�^
TextureManager::TextureManager( ITextureLoader* pLoader ) :
    p_loader_( pLoader )
{
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

    delete p_loader_;
}

// �ǂݍ���
bool TextureManager::load( const std::wstring& Path, ITexture** ppTexture )
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
void TextureManager::unload( ITexture** ppTexture )
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
void TextureManager::create( const EasyEngine& Creator, ITextureLoader* pLoader )
{
    destroy( Creator );
    instance_ = new TextureManager( pLoader );
}
// �j������
void TextureManager::destroy( const EasyEngine& Deleter )
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
