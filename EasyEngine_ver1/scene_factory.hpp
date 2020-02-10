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
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          シーンの登録にはREGISTER_SCENEマクロを使用して下さい。
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


class REGISTER_SCENE
{
public :
    REGISTER_SCENE( uint32_t ID, EGEG Scene*(*pFunc)() ) { EGEG SceneFactory::instance()->registerCreator( ID, pFunc); }
};
///
/// @def     REGISTER_SCENE
/// @brief   シーンをファクトリに登録
/// @details ヘッダーファイルで呼び出さないでください。
///
/// @param[in] SceneID  : シーンの生成ID
/// @param[in] pCreator : 生成ファンクタ
///
#define REGISTER_SCENE( SceneID, pCreator ) \
namespace impl{} namespace { namespace impl { \
REGISTER_SCENE register_scene( SceneID, pCreator ); \
}}
#endif /// !INCLUDED_EGEG_SCENE_FACTORY_HEADER_
/// EOF
