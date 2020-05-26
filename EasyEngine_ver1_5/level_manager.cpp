// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "level_manager.hpp"
#include <fstream>
#include "engine.hpp"
#include "level.hpp"


BEGIN_EGEG

/******************************************************************************

	LevelManager

******************************************************************************/
 // �R���X�g���N�^
LevelManager::LevelManager() noexcept = default;


 // �f�X�g���N�^
LevelManager::~LevelManager()
{
    for( auto& level : levels_ )
    {
        level->finalize();
    }
}


 // ����
std::unique_ptr<LevelManager> LevelManager::create()
{
    std::unique_ptr<LevelManager> created( new LevelManager{} );
    auto start_level = created->createLevel( "Resource/Levels/start.lvl" );
    if( !start_level ) return nullptr;
    created->levels_.push_back( std::move(start_level) );
    created->transition_path_.emplace_back( "Resource/Levels/start.lvl" );
    created->task_.setJob( created.get(), &LevelManager::destructionFinalizedLevel );
    EasyEngine::getTaskManager()->registerJob( &created->task_ );

    return created;
}


 // ���x���̐���
std::unique_ptr<Level> LevelManager::createLevel( const std::string& FilePath )
{
    std::fstream stream{ FilePath };
    if( !stream ) return nullptr;

    std::string data;
    while( stream >> data )
    { // �t�@�C������A���x���^�C�v��������
        if( data == "Level" )
        { // ���x���̐���
            stream >> data;
            auto level = LevelFactory::create( data );
            if( !level->initialize(stream) )
                return nullptr;
            return level;
        }
    }

    stream.close();
    return nullptr;
}


 // �J��
 //
 // note : �����̕�����͓����ŃR�s�[���邽�߂����Ēl�n���B
 //        std::string��move�������Ȃ̂Ő��藧�B
void LevelManager::transition( std::string FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    // �ێ����Ă��郌�x����S�Ĕj�����A�V�K�Ƀ��x����ǉ�
    for( auto& level : levels_ )
        finalized_levels_.push_back( std::move(level) );
    levels_.clear();
    levels_.push_back( std::move(next) );

    // �����̒ǉ�
    auto find_itr = std::find( transition_path_.begin(), transition_path_.end(), FilePath );
    if( find_itr != transition_path_.end() )
    { // �����ɂ��郌�x���ւ̑J��
        // �����������܂Ŗ߂�
        path_index_ = std::distance( transition_path_.begin(), find_itr );
    }
    else
    { // �����ɂȂ����x���ւ̑J��
        // �V�K�ɗ�����ǉ�
        if( ++path_index_ >= transition_path_.size() )
            transition_path_.push_back( std::move(FilePath) );
        else
            transition_path_.at(path_index_) = std::move(FilePath);
    }
}


 // �ǉ�
void LevelManager::push( const std::string& FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    levels_.push_back( std::move(next) );
}


 // ����ւ�
 //
 // note : �����ɂ��ẮApush()�Ɠ������
void LevelManager::swap( std::string FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    finalized_levels_.push_back( std::move(levels_.back()) );
    levels_.push_back( std::move(next) );

    transition_path_.at( path_index_ ) = std::move(FilePath);
}


 // 1�߂�
void LevelManager::back()
{
    if( levels_.size() > 1U )
    { // �߂��C���X�^���X������
        finalized_levels_.push_back( std::move(levels_.back()) );
        levels_.pop_back();
    }
    else
    { // �C���X�^���X������
        // ����̃��x���t�@�C�����Q�Ƃ��Đ������ꂽ���x���t�@�C���Ɠ���ւ���B
        // ���̎��A�C���f�b�N�X���߂��Ă���̂ŁA���܂�����
        swap( transition_path_.at(--path_index_) );
    }
}


 // �폜�ς݃��x���̔j��
 //
 // note : �J�ڂƓ����t���[���ɑJ�ڌ��̃��x���폜���Ă��܂��ƁA
 //        �J�ڌ�ɔj��ς݃��x���ɃA�N�Z�X�����ۖ������`�ƂȂ��Ă��܂��̂ŁA
 //        �j������̃t���[���ɒx�������Ă���B
void LevelManager::destructionFinalizedLevel( uint64_t )
{
    // �t���ɏI���������Ăяo���Ă���
    for( auto ritr = finalized_levels_.rbegin(),
              rend = finalized_levels_.rend();
        ritr != rend; ++ritr )
    {
        (*ritr)->finalize();
    }
    finalized_levels_.clear();
}

END_EGEG
// EOF
