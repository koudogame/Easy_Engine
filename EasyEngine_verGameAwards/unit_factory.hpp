///
/// @file   unit_factory.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_UNIT_FACTORY_HEADER_
#define INCLUDED_EGEG_UNIT_FACTORY_HEADER_
#include <unordered_map>
#include <memory>
#include "uid.hpp"
#include "game_unit.hpp"
BEGIN_EGEG
template <class T>
class Creator;

///
/// @class  UnitFactory
/// @brief  ���j�b�g�̃t�@�N�g��
///
class UnitFactory
{
public :
    template <class T>
    using CreateType = std::unique_ptr<T, void(*)(GameUnit*)>;

    template <class T, class ...Args>
    CreateType<T> create( Args&&... Args ) const;

    template <class T, class ...Args>
    void regist( T*(*Function)(Args...) );

private :
    std::unordered_map<uint32_t, GameUnit*(*)()> creators_;
};

///< ��������
template <class T, class ...Args>
UnitFactory::CreateType<T> UnitFactory::create( Args&&... args) const
{
    auto deleter = [](GameUnit* Delete){ Delete->finalize(); delete Delete; };
    CreateType<T> ptr( nullptr, deleter );

    auto creator = creators_.find( UID<T>() );
    assert( creator != creators_.end() && "�N���G�C�^�[���o�^����Ă��܂���B" );
    
    // �����������o�^����Ă���ꍇ
    if( creator != creators_.end() )
    {
        ptr.reset( static_cast<T*>(creator->second(std::forward<Args>(args)...)) );
    }

    return ptr;
}

///< ���������o�^
template <class T, class ...Args>
void UnitFactory::regist( T*(*Function)(Args...) )
{
    creators_.emplace( UID<T>(), Function );
}
END_EGEG
#endif /// !INCLUDED_EGEG_UNIT_FACTORY_HEADER_
/// EOF
