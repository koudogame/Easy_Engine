// 作成者 : 板場
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
 // コンストラクタ
LevelManager::LevelManager() noexcept = default;


 // デストラクタ
LevelManager::~LevelManager()
{
    for( auto& level : levels_ )
    {
        level->finalize();
    }
}


 // 生成
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


 // レベルの生成
std::unique_ptr<Level> LevelManager::createLevel( const std::string& FilePath )
{
    std::fstream stream{ FilePath };
    if( !stream ) return nullptr;

    std::string data;
    while( stream >> data )
    { // ファイルから、レベルタイプを見つける
        if( data == "Level" )
        { // レベルの生成
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


 // 遷移
 //
 // note : 引数の文字列は内部でコピーするためあえて値渡し。
 //        std::stringはmoveが高速なので成り立つ。
void LevelManager::transition( std::string FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    // 保持しているレベルを全て破棄し、新規にレベルを追加
    for( auto& level : levels_ )
        finalized_levels_.push_back( std::move(level) );
    levels_.clear();
    levels_.push_back( std::move(next) );

    // 履歴の追加
    auto find_itr = std::find( transition_path_.begin(), transition_path_.end(), FilePath );
    if( find_itr != transition_path_.end() )
    { // 履歴にあるレベルへの遷移
        // 履歴をそこまで戻す
        path_index_ = std::distance( transition_path_.begin(), find_itr );
    }
    else
    { // 履歴にないレベルへの遷移
        // 新規に履歴を追加
        if( ++path_index_ >= transition_path_.size() )
            transition_path_.push_back( std::move(FilePath) );
        else
            transition_path_.at(path_index_) = std::move(FilePath);
    }
}


 // 追加
void LevelManager::push( const std::string& FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    levels_.push_back( std::move(next) );
}


 // 入れ替え
 //
 // note : 引数については、push()と同じ解説
void LevelManager::swap( std::string FilePath )
{
    auto next = createLevel( FilePath );
    if( !next ) return;

    finalized_levels_.push_back( std::move(levels_.back()) );
    levels_.push_back( std::move(next) );

    transition_path_.at( path_index_ ) = std::move(FilePath);
}


 // 1つ戻る
void LevelManager::back()
{
    if( levels_.size() > 1U )
    { // 戻れるインスタンスがある
        finalized_levels_.push_back( std::move(levels_.back()) );
        levels_.pop_back();
    }
    else
    { // インスタンスが無い
        // 一つ後ろのレベルファイルを参照して生成されたレベルファイルと入れ替える。
        // この時、インデックスも戻しているので、うまくいく
        swap( transition_path_.at(--path_index_) );
    }
}


 // 削除済みレベルの破壊
 //
 // note : 遷移と同じフレームに遷移元のレベル削除してしまうと、
 //        遷移後に破壊済みレベルにアクセスした際未動作定義となってしますので、
 //        破壊を次のフレームに遅延させている。
void LevelManager::destructionFinalizedLevel( uint64_t )
{
    // 逆順に終了処理を呼び出している
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
