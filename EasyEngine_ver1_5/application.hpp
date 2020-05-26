///
/// @file   application.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_

#ifdef _DEBUG
#include <cassert>
#endif
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @class Application
/// @brief アプリケーションインスタンス
///
/// @details シングルトンクラスです。グローバルアクセスは提供しません。
///
class Application final
{
public :
    Application() noexcept
    {
#ifdef _DEBUG
    static int create_cnt_;
    assert( !create_cnt_++ && "アプリケーションインスタンスを複数生成することはできません。" );
#endif
    }
    void operator()() const;
};

END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
