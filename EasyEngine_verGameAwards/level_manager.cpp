// �쐬�� : ��
#include "level_manager.hpp"
#include "level.hpp"

BEGIN_EGEG

// LevelManager �֐���`
/*===========================================================================*/
// ���x���̐���
std::unique_ptr<Level> LevelManager::createLevel( uint32_t ID )
{
    std::unique_ptr<Level> ptr( LevelFactory::create(ID, this) );
    if( ptr && ptr->initialize() ) return ptr;

    ptr.reset( nullptr );
    return ptr;
}

// ���x���̑J��
void LevelManager::transition( uint32_t NextID )
{
     // �J�ڐ�̃��x���𐶐�
    auto level = createLevel( NextID );
    if( !level ) 
    { // ���x���̐����Ɏ��s
        return;
    }

    // �ێ����Ă��郌�x�������ׂĔj�����A�V�K�Ƀ��x����ǉ�
    for( auto& prev : level_list_ )
        prev->finalize();
    level_list_.clear();
    level_list_.push_back( std::move(level) );

    // ������ǉ�
    if( auto find = std::find(transition_path_.begin(), transition_path_.end(), NextID);
        find != transition_path_.end() )
    { // �����ɂ��郌�x���ւ̑J��
        // �����������܂Ŗ߂�
        path_idx_ = std::distance( transition_path_.begin(), find );
    }
    else
    { // �����ɂȂ����x���ւ̑J��
        // �V�K�ɑJ�ڗ�����ǉ�
        if( ++path_idx_ >= transition_path_.size() )
            transition_path_.push_back( NextID );
        else
            transition_path_.at(path_idx_) = NextID;
    }
}

// ���x���̒ǉ�
void LevelManager::push( uint32_t NextID )
{
    // �J�ڐ�̃��x���𐶐�
    auto level = createLevel( NextID );
    if( !level ) 
    { // ���x���̐����Ɏ��s
        return;
    }

    // ���x���̒ǉ�( ����ւ��ł͂Ȃ� )
    level_list_.push_back( std::move(level) );
}

// ���x���̓���ւ�
void LevelManager::swap( uint32_t NextID )
{
    // �J�ڐ�̃��x���𐶐�
    auto level = createLevel( NextID );
    if( !level )
    { // ���x���̐����Ɏ��s
        return;
    }

    // ���݂̃��x����j�����A�J�ڐ�̃��x���Ɠ���ւ���
    level_list_.back()->finalize();
    level_list_.back() = std::move( level );

    // �J�ڗ�����ύX
    transition_path_.at( path_idx_ ) = NextID;
}

// ��߂�
void LevelManager::back()
{
    if( level_list_.size() > 1U )
    { // �߂��C���X�^���X���c���Ă���
        // �ێ�����C���X�^���X�֑J�ځA�����ɕύX�͂Ȃ�
        level_list_.back()->finalize();
        level_list_.pop_back();
    }
    else if( path_idx_ > 0 )
    { // �߂��C���X�^���X���Ȃ�
        // �J�ڗ������Q�Ƃ��J�ڂ���
        swap( transition_path_.at(--path_idx_) );
    }

    // �߂�悪�����ꍇ�A�������Ȃ�
}

END_EGEG
// EOF
