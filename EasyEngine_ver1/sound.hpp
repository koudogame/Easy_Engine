///
/// @file   sound.hpp
/// @author ��
///
/// @brief  �T�E���h�f�[�^
///
#ifndef INCLUDED_EGEG_SOUND_HEADER_
#define INCLUDED_EGEG_SOUND_HEADER_
#include "shared_object.hpp"
BEGIN_EGEG
class ISound :
    public SharedObject
{
protected :
    virtual ~ISound() = 0 {}
};
END_EGEG
#endif /// !INCLUDED_EGEG_SOUND_HEADER_
/// EOF
