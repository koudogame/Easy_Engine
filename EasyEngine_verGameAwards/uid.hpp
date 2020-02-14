///
/// @file   uid.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_UID_HEADER_
#define INCLUDED_EGEG_UID_HEADER_
#include <cstdint>
///
/// @class  UID
/// @brief  �^��񂩂�ID���擾����N���X
/// 
class UID
{
public :
    ///
    /// @brief  �^����ID���擾����
    ///
    /// @tparam Object : ID���擾����N���X�^
    ///
    /// @return ID
    ///
    template <class Object>
    static uint32_t getID() noexcept { static uint32_t uid = reinterpret_cast<uint32_t>(&uid); return uid; }

    ///
    /// @brief  �C���X�^���X����ID���擾����
    ///
    /// @tparam Object : ID���擾����N���X�^(�ȗ���)
    /// @param[in] : ID���擾����I�u�W�F�N�g�C���X�^���X
    ///
    /// @return ID
    ///
    template <class Object>
    static uint32_t getID( const Object& ) noexcept { return UID::getID<Object>(); }
};
#endif /// !INCLUDED_EGEG_UID_HEADER_
/// EOF
