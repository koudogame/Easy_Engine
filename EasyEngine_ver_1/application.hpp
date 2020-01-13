///
/// @file    application.hpp
/// @author  ��
///          
/// @brief   �A�v���P�[�V�����̃G���g���[�N���X
/// @details �V���O���g���N���X�ł��B�C���X�^���X�ւ̕�����������̃A�N�Z�X���֎~���Ă��܂��B
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
        assert( !not_first++ && "�C���X�^���X�ւ̕�����������̃A�N�Z�X�͋֎~���Ă��܂��B" );
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
