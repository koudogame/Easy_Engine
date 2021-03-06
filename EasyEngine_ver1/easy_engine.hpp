///
/// @file    easy_engine.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_
#include <string>
#ifdef _DEBUG
#include <cassert>
#endif /// !_DEBUG
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  EasyEngine
///          
/// @brief   EasyEngine本体
/// @details アプリケーションのエントリークラスです。<br>
///          シングルトンクラスです。グローバルアクセスは提供しません。
///
class EasyEngine final
{
public :
    EasyEngine()
    {
#ifdef _DEBUG
        assert( !create_cnt_++ && "既に生成されています。" );
#endif /// !_DEBUG
    }

    ///
    /// @brief  実行
    ///
    /// @param[in] Platform : ゲームのプラットフォーム
    ///
    void run( const std::string& Platform );

    ///
    /// @brief   EasyEngine本体である証明
    /// @details この関数が呼び出せれば、EasyEngineクラス本体である。
    ///
    void proof() const {}
private :
#ifdef _DEBUG
    static int create_cnt_;
#endif /// !_DEBUG
};
END_EGEG
#endif /// !INCLUDED_EGEG_EASY_ENGINE_HEADER_
/// EOF
