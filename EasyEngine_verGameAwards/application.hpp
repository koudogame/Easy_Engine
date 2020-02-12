///
/// @file   application.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif // !_DEBUG
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Application
/// @brief   アプリケーションエントリー
///          
/// @details シングルトンクラスです。グローバルアクセスは提供しません。<br>
///
class Application
{
public:
    inline Application()
    {
#ifdef _DEBUG
        static int create_cnt_;
        assert(!create_cnt_ && "既に生成されています。");
#endif // !_DEBUG
    }

    void run();

private:
    bool initialize();
    void finalize();
    void mainLoop();

    Application( const Application& ) = delete;
    Application& operator=( const Application& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
