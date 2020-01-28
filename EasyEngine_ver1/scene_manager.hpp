///
/// @file    scene_manager.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_SCENE_MANAGER_HEADER_
#define INCLUDED_EGEG_SCENE_MANAGER_HEADER_
#include <deque>
#include "scene.hpp"
BEGIN_EGEG
///
/// @class  SceneManager
///
/// @brief   シーンマネージャー
/// @details シングルトンクラスです。アクセスにはinstance関数を使用してください。<br>
///          シーンはスタック管理です。最も最後に追加されたシーンをアクティブとします。<br>
///          pop,swap関数は内部でアクティブシーンの開放を行っています。<br>
///          この関数の呼び出し後、アクティブシーンのを指すポインタはダングリングポインタになります。
///
class SceneManager
{
public :
    ~SceneManager();

    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static SceneManager* instance() { static SceneManager i; return &i; }

    ///
    /// @brief   シーンを追加する
    /// @details シーンのロードが実行されます。
    ///
    /// @param[in] SceneID : 追加するシーンのID
    ///
    void push( uint32_t SceneID );
    ///
    /// @brief   最後に追加されたシーンを削除する
    /// @details シーンが複数存在する場合のみ有効です。
    ///
    void pop();
    ///
    /// @brief   シーンを入れ替える
    /// @details シーンのロードが実行されます。
    ///
    /// @param[in] SceneID : 入れ替え後のシーンID
    ///
    void swap( uint32_t SceneID );

private :
    SceneManager();
    SceneManager( const SceneManager& ) = delete;
    SceneManager& operator=( const SceneManager& ) = delete;

    std::deque<Scene*> scenes_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_MANAGER_HEADER_
/// EOF
