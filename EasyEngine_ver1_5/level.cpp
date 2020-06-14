// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "level.hpp"
#include <fstream>
#include "engine.hpp"
#include "task_order.hpp"
#include "level_scene.hpp"


BEGIN_EGEG

/******************************************************************************

    Level

******************************************************************************/
 // 初期化
bool Level::load( const std::string& LevelFile )
{
    std::fstream stream{ LevelFile, std::ios::in };
    if( !stream ) return false;
    if( !loadNodes(stream) ) return false;

    // タスクを登録
    task_update_.setJob( &task_manager_, &decltype(task_manager_)::execute );
    EasyEngine::getTaskManager()->registerJob( &task_update_, TaskOrder::kLevelUpdate );
    task_render_.setJob( root_node_->getChild<LevelScene>(), &LevelScene::render );
    EasyEngine::getTaskManager()->registerJob( &task_render_, TaskOrder::kRendering );

    return true;
}


 // 終了
void Level::unload()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_render_ );
    EasyEngine::getTaskManager()->unregisterJob( &task_update_ );

    root_node_.reset();
}


 // ポーズ
void Level::pause()
{
    EasyEngine::getTaskManager()->unregisterJob( &task_update_ );
}


 // ポーズ解除
void Level::unpause()
{
    EasyEngine::getTaskManager()->registerJob( &task_update_, TaskOrder::kLevelUpdate );
}


 // 全てのノードを読み込む
bool Level::loadNodes( std::istream& Stream )
{
    // ルートノードを生成
    root_node_ = std::make_unique<LevelEmpty>();

    std::string term;
    while( Stream >> term )
    {
        if( term=="BeginLevel" )
            break;
    }

    while( Stream >> term )
    {
        if( term=="EndLevel" )
            break;

        root_node_->addChild( loadNode(term, Stream) );
    }

    return true;
}


 // ノードを読み込む
std::unique_ptr<LevelNode> Level::loadNode( std::string& Term, std::istream& Stream )
{
    std::unique_ptr<LevelNode> node{ LevelNodeFactory::create(Term) };
    while( !node )
    {
        Stream >> Term;
        node = LevelNodeFactory::create( Term );
    }

    if( !node->initialize(Stream) )
        node.reset();

    while( Stream >> Term )
    {
        if( Term==";" ) break;
        if( node ) // ノードの初期化に失敗した場合でも、文末まで読み込む
            node->addChild( loadNode(Term, Stream) );
    }


    return node;
}

END_EGEG
// EOF
