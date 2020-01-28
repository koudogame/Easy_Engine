///
/// @file   scene_factory.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE_FACTORY_HEADER_
#define INCLUDED_EGEG_SCENE_FACTORY_HEADER_
#include "factory.hpp"
#include "scene.hpp"
BEGIN_EGEG
///
/// @class   SceneFactory
///          
/// @brief   シーンファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
class SceneFactory :
    public Factory<Scene, Scene*(*)()>
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static SceneFactory* instance() { static SceneFactory i; return &i; }

private :
    SceneFactory() = default;
    SceneFactory( const SceneFactory& ) = delete;
    SceneFactory& operator=( const SceneFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_FACTORY_HEADER_
/// EOF
