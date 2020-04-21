///
/// @file   type_id.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TYPE_ID_HEADER_
#define INCLUDED_EGEG_TYPE_ID_HEADER_

#include <cstdint>
#include "utility_function.hpp"

BEGIN_EGEG

///
/// @class  TypeID
/// @brief  �^��񂩂�ID���擾����N���X
///
/// @tparam Type : ID���擾����^
/// 
template <class Type>
class TypeID
{
public :
    constexpr TypeID() noexcept = default;

    operator ::std::uintptr_t() const noexcept
    {
        return id_;
    }
    ::std::uintptr_t operator()() const noexcept
    {
        return *this;
    }
private :
    static const ::std::uintptr_t id_;
};

template <class Type>
const ::std::uintptr_t TypeID<Type>::id_{ uniqueid_cast<::std::uintptr_t>(id_) };

END_EGEG
#endif /// !INCLUDED_EGEG_TYPE_ID_HEADER_
/// EOF
