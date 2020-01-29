///
/// @file   uid.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  UID
///
/// @brief  �N���X���ɌŗL��ID�𐶐�
///
/// @tparam Object : ID�𐶐�����N���X�^
///
template <class Object>
class UID
{
public :
    ///
    /// @brief  �I�u�W�F�N�g�̌^�ɑΉ�����UID�̎擾
    ///
    /// @return UID
    ///
    static uint32_t ID() noexcept { static uint32_t uid = reinterpret_cast<uint32_t>(&uid); return uid; }
};
END_EGEG
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
