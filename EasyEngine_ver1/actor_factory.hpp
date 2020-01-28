///
/// @file   actor_factory.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
#define INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
#include "factory.hpp"
#include "actor.hpp"
BEGIN_EGEG
///
/// @class   ActorFactory
///          
/// @brief   アクターファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
class ActorFactory :
    public Factory<Actor, Actor*(*)()>
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static ActorFactory* instance() { static ActorFactory i; return &i; }

private :
    ActorFactory() = default;
    ActorFactory( const ActorFactory& ) = delete;
    ActorFactory& operator=( const ActorFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR_FACTORY_HEADER_
/// EOF
