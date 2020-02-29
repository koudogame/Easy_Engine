///
/// @file   application.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_APPLICATION_HEADER_
#define INCLUDED_EGEG_APPLICATION_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class   Application
/// @brief   アプリケーションエントリー
///          
/// @details シングルトンクラスです。グローバルアクセスは提供しません。<br>
///
class Application final
{
public:
    inline Application() noexcept
    {
#ifdef _DEBUG
        static int create_cnt_;
        assert(!create_cnt_++ && "既に生成されています。");
#endif // !_DEBUG
    }

    ///
    /// @brief  アプリケーションの実行
    ///
    void run();


    Application( const Application& ) = delete;
    Application& operator=( const Application& ) = delete;
private :
    bool initialize();
    void finalize();
    void mainloop();
};
END_EGEG
#endif /// !INCLUDED_EGEG_APPLICATION_HEADER_
/// EOF
