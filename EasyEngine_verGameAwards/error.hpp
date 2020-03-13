///
/// @file   error.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ERROR_HEADER_
#define INCLUDED_EGEG_ERROR_HEADER_
#include <tchar.h>
#include <Windows.h>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  Error
/// @brief  �G���[�\���_�C�A���O�{�b�N�X�̕\��
///
class Error
{
public :
    ///
    /// @brief  �G���[���b�Z�[�W���_�C�A���O�{�b�N�X�ŏo��
    ///
    /// @param[in] Message : �o�͂��镶����
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
