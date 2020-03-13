///
/// @file   error.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ERROR_HEADER_
#define INCLUDED_EGEG_ERROR_HEADER_
#include <tchar.h>
#include <Windows.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  Error
/// @brief  エラー表示ダイアログボックスの表示
///
class Error
{
public :
    ///
    /// @brief  エラーメッセージをダイアログボックスで出力
    ///
    /// @param[in] Message : 出力する文字列
    ///
    static void showErrorMessage( const TCHAR* Message )
    {
         MessageBox(
            0,
            Message,
            _T("Error"),
            MB_OK | MB_ICONERROR 
         );
    }
};
END_EGEG
#endif /// !INCLUDED_EGEG_ERROR_HEADER_
/// EOF
