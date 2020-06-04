///
/// @file   id.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ID_HEADER_
#define INCLUDED_EGEG_ID_HEADER_

#include <cstdint>
#include <type_traits>
#include "egeg_def.hpp"
#include "raw_number.hpp"

BEGIN_EGEG

namespace impl
{
template <class ValueType, class T, class IsSigned>
ValueType uniqueid_impl( const T& Instance, IsSigned );
}


///
/// @brief  �C���X�^���X���Ɉ�ӂ�ID���擾����
///
/// @tparam ValueType  : �擾����ID�̌^
///
template <class ValueType, class T>
ValueType uniqueid( const T& Instance )
{
    return impl::uniqueid_impl<ValueType>(Instance, std::is_signed<ValueType>{} );
}


///
/// @class  ConstantID
/// @brief  �萔�lID
/// @details ���l�^�A�������͗񋓌^�ȊO�̃p�����[�^���󂯎��܂���B
///
template <auto Value, class IsEnum=std::is_enum<decltype(Value)>, class=std::enable_if_t<std::is_arithmetic<decltype(Value)>::value || IsEnum::value>>
struct ConstantID
{
    operator typename RawNumber<Value>::NumTy() const noexcept
    {
        return RawNumber<Value>::value;
    }
    
    typename RawNumber<Value>::NumTy operator()() const noexcept
    {
        return RawNumber<Value>::value;
    }
};
///< ��񋓎q�p�������ꉻ
template <auto Value>
struct ConstantID<Value, std::false_type>
{
    operator decltype(Value)() const noexcept
    {
        return Value;
    }

    decltype(Value) operator()() const noexcept
    {
        return Value;
    }
};


///
/// @class  TypeID
/// @brief  �^���Ɉ�ӂ�ID
///
/// @tparam NodeType      : ID���擾����^
/// @tparam ValueType : ID�̌^( �f�t�H���g��std::uintptr_t )
///
template <class Type, class ValueType=std::uintptr_t>
class TypeID
{
public :
    operator ValueType() const noexcept
    {
        return id_;
    }
    ValueType operator()() const noexcept
    {
        return id_;
    }
private :
    static const ValueType id_;
};
template <class Type, class ValueType>
const ValueType TypeID<Type, ValueType>::id_{ uniqueid<ValueType>(id_) };






namespace impl
{
template <class ValueType, class T, class IsSigned>
ValueType uniqueid_impl( const T& Instance, IsSigned )
{
    return static_cast<ValueType>(reinterpret_cast<std::intptr_t>(&Instance));
}
template <class ValueType, class T>
ValueType uniqueid_impl( const T& Instance, std::false_type )
{
    return static_cast<ValueType>(reinterpret_cast<std::uintptr_t>(&Instance));
}
}

END_EGEG
#endif /// !INCLUDED_EGEG_ID_HEADER_
/// EOF
