///
/// @file    easy_engine.hpp
/// @author  ��
///          
/// @brief   EasyEngine�{��
/// @details �A�v���P�[�V�����̃G���g���[�N���X�ł��B<br>
///          �V���O���g���N���X�ł��B�O���[�o���A�N�Z�X�͒񋟂��܂���B
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_
#ifdef _DEBUG
#include <cassert>
#endif /// !_DEBUG
#include "egeg_common.hpp"
BEGIN_EGEG
class EasyEngine final
{
public :
    EasyEngine()
    {
#ifdef _DEBUG
        assert( !create_cnt_++ && "���ɐ�������Ă��܂��B" );
#endif /// !_DEBUG
    }

    ///
    /// @brief  ���s
    ///
    /// @param[in] Platform : �Q�[���̃v���b�g�t�H�[��
    ///
    void run( const char* Platform );

    ///
    /// @brief   EasyEngine�{�̂ł���ؖ�
    /// @details ���̊֐����Ăяo����΁AEasyEngine�N���X�{�̂ł���B
    ///
    void proof() {}
private :
#ifdef _DEBUG
    static int create_cnt_;
#endif /// !_DEBUG
};
END_EGEG
#endif /// !INCLUDED_EGEG_EASY_ENGINE_HEADER_
/// EOF
