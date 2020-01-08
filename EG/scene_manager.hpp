///
/// @file    scene_manager.hpp
/// @author  板場
///
/// @brief   シーン管理クラス<br>
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。<br>
///          シーンの扱いはstack(後入れ先出し)です。<br>
///          最後に追加されたシーンをアクティブなシーンとして扱います。
///
///
#ifndef INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#define INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
#include <vector>
#include "easy_engine.hpp"
BEGIN_EG_EG
class Scene;
class SceneManager
{
public :
    ///
    /// @brief  インスタンスを取得します。
    ///
    /// @return インスタンスへのアドレス
    ///
    static SceneManager* instance() { static SceneManager i; return &i; }

    ///
    /// @brief 保持しているシーンすべてのupdata関数を呼び出します。
    ///
    void update();
    
    ///
    /// @brief  保持しているシーンすべてのdraw関数を呼び出します。
    ///
    void draw();

    ///
    /// @brief  アクティブなシーンを取得します。
    ///
    /// @return アクティブなシーンへのポインタ
    ///
    inline Scene* getActive() const { return scenes_.back(); }

    ///
    /// @brief      シーンを追加します。
    ///
    /// @param[in]  pNext : 追加するシーンのアドレス
    ///
    inline void push( Scene* pNext ) { scenes_.push_back( pNext ); }

    ///
    /// @brief シーンを除外します。
    ///
    void pop();

    ///
    /// @brief シーンを入れ替えます。
    ///
    /// @param[in] pNext : 入れ替え後のシーンのアドレス
    ///
    void swap( Scene* pNext );

private :
    std::vector<Scene*> scenes_;    ///<    @brief シーンリスト
    Scene* poped_scene_ = nullptr;  ///<    @brief 除外したシーンを一時格納しておく

    SceneManager() = default;
};
END_EG_EG
#endif /// INCLUDED_EG_EG_SCENE_MANAGER_HEADER_
/// EOF
