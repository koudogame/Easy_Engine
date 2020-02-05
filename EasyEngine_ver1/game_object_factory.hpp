///
/// @file   game_object_factory.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
#include "factory.hpp"
#include "game_object.hpp"
BEGIN_EGEG
///
/// @class  GameObjectFactory
/// @brief  ゲームオブジェクトのファクトリ
///
class GameObjectFactory :
    public Factory<GameObject, GameObject*(*)()>
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static GameObjectFactory* instance() { static GameObjectFactory i; return &i; }

private :
    GameObjectFactory() = default;
    GameObjectFactory( const GameObjectFactory& ) = delete;
    GameObjectFactory& operator=( const GameObjectFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_FACTORY_HEADER_
/// EOF
