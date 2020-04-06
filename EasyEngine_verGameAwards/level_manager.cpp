// 作成者 : 板場
#include "level_manager.hpp"
#include "level.hpp"

BEGIN_EGEG

// LevelManager 関数定義
/*===========================================================================*/
// レベルの生成
std::unique_ptr<Level> LevelManager::createLevel( uint32_t ID )
{
    std::unique_ptr<Level> ptr( LevelFactory::create(ID, this) );
    if( ptr && ptr->initialize() ) return ptr;

    ptr.reset( nullptr );
    return ptr;
}

// レベルの遷移
void LevelManager::transition( uint32_t NextID )
{
     // 遷移先のレベルを生成
    auto level = createLevel( NextID );
    if( !level ) 
    { // レベルの生成に失敗
        return;
    }

    // 保持しているレベルをすべて破棄し、新規にレベルを追加
    for( auto& prev : level_list_ )
        prev->finalize();
    level_list_.clear();
    level_list_.push_back( std::move(level) );

    // 履歴を追加
    if( auto find = std::find(transition_path_.begin(), transition_path_.end(), NextID);
        find != transition_path_.end() )
    { // 履歴にあるレベルへの遷移
        // 履歴をそこまで戻す
        path_idx_ = std::distance( transition_path_.begin(), find );
    }
    else
    { // 履歴にないレベルへの遷移
        // 新規に遷移履歴を追加
        if( ++path_idx_ >= transition_path_.size() )
            transition_path_.push_back( NextID );
        else
            transition_path_.at(path_idx_) = NextID;
    }
}

// レベルの追加
void LevelManager::push( uint32_t NextID )
{
    // 遷移先のレベルを生成
    auto level = createLevel( NextID );
    if( !level ) 
    { // レベルの生成に失敗
        return;
    }

    // レベルの追加( 入れ替えではない )
    level_list_.push_back( std::move(level) );
}

// レベルの入れ替え
void LevelManager::swap( uint32_t NextID )
{
    // 遷移先のレベルを生成
    auto level = createLevel( NextID );
    if( !level )
    { // レベルの生成に失敗
        return;
    }

    // 現在のレベルを破棄し、遷移先のレベルと入れ替える
    level_list_.back()->finalize();
    level_list_.back() = std::move( level );

    // 遷移履歴を変更
    transition_path_.at( path_idx_ ) = NextID;
}

// 一つ戻る
void LevelManager::back()
{
    if( level_list_.size() > 1U )
    { // 戻れるインスタンスが残っている
        // 保持するインスタンスへ遷移、履歴に変更はない
        level_list_.back()->finalize();
        level_list_.pop_back();
    }
    else if( path_idx_ > 0 )
    { // 戻れるインスタンスがない
        // 遷移履歴を参照し遷移する
        swap( transition_path_.at(--path_idx_) );
    }

    // 戻る先が無い場合、何もしない
}

END_EGEG
// EOF
