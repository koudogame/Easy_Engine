///
/// @file    application.hpp
/// @author  板場
///          
/// @brief   アプリケーションのエントリークラス
/// @details シングルトンクラスです。インスタンスへの複数方向からのアクセスを禁止しています。
///
#ifndef INCLUDED_EG_EG_APPLICATION_HEADER_
#define INCLUDED_EG_EG_APPLICATION_HEADER_
#include <assert.h>
#include "egeg.hpp"
BEGIN_EGEG
class Application
{
public :
    static Application* instance()
    {
#ifdef _DEBUG
        static unsigned not_first = 0U;
        assert( !not_first++ && "インスタンスへの複数方向からのアクセスは禁止しています。" );
#endif
        Application i;
        return &i;
    }

    void execute();

private :
    Application() = default;
};
END_EGEG
#endif /// !INCLUDED_EG_EG_APPLICATION_HEADER_
/// EOF
