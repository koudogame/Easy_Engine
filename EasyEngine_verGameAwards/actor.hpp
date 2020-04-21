///
/// @file   actor.hpp
/// @author ��
///
#ifndef INCLUDED_ACTOR_HEADER_
#define INCLUDED_ACTOR_HEADER_
#include <cstdint>
#include <unordered_map>
#include "egeg.hpp"
BEGIN_EGEG
namespace component { class Component; } ///< �R���|�[�l���g�O���錾( �z�Q�Ɖ�� )

///
/// @class  Actor
/// @brief  �A�N�^�[���
///
class Actor
{
public :
    virtual ~Actor();

    ///
    /// @brief  �A�N�^�[����ID�̎擾
    ///
    /// @return �A�N�^�[����ID
    ///
    uint32_t getID() const noexcept { return id_; }

    ///
    /// @brief  �A�N�^�[����������
    ///
    /// @return ����������[ true ]�@���������s[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  �A�N�^�[�I������
    ///
    virtual void finalize() = 0;
    
    ///
    /// @brief   �R���|�[�l���g�̎擾
    /// @details �Ή�����R���|�[�l���g���Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam ComponentType : �擾����R���|�[�l���g�^
    ///
    /// @return �R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;
protected :
    Actor( uint32_t ActorID ) noexcept : id_( ActorID ) {}
    std::unordered_map<uint32_t, component::Component*> components_; ///< �R���|�[�l���g

private :
    uint32_t id_;   /// �A�N�^�[����ID
};

///< �R���|�[�l���g�̎擾
template <class ComponentType>
ComponentType* Actor::getComponent() const
{
    auto find = components_.find( ComponentType::getID() );
    if( find == components_.end() ) return nullptr;

    // �Ή�����R���|�[�l���g�̕ԋp
    return static_cast<ComponentType*>( find->second );
}

END_EGEG
#endif /// !INCLUDED_ACTOR_HEADER_
/// EOF
