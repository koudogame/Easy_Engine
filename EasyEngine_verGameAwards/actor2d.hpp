///
/// @file   actor2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR2D_HEADER_
#define INCLUDED_EGEG_ACTOR2D_HEADER_

#include <cassert>
#include <list>
#include "actor.hpp"
#include "type_id.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Actor2D
/// @brief  2D�A�N�^�[
///
class Actor2D :
    public Actor
{
public :
    ///< �f�X�g���N�^
    virtual ~Actor2D() = default;

    ///
    /// @brief  �R���|�[�l���g�̒ǉ�
    ///
    /// @tparam ComponentType : �ǉ�����R���|�[�l���g�^
    ///
    /// @return �ǉ������R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* addComponent();
    ///
    /// @brief   �R���|�[�l���g�̎擾
    /// @details �Ή������R���|�[�l���g���������Ă��Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam ComponentType : �擾����R���|�[�l���g�^
    ///
    /// @return �R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

protected :
    Actor2D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}
};


///< �R���|�[�l���g�̒ǉ�
template <class ComponentType>
ComponentType* Actor2D::addComponent()
{
    assert( getComponent<ComponentType>() == nullptr &&
        "�R���|�[�l���g�̑��d�o�^�����o���܂����B" );

    // �R���|�[�l���g�̐���
    ComponentType* component = new ComponentType( this );
    component->initialize();

    // ���������R���|�[�l���g�����X�g�ɒǉ�
    components_.emplace( ComponentType::getID(), component );

    return component;
}

///< �R���|�[�l���g�̎擾
template <class ComponentType>
ComponentType* Actor2D::getComponent() const
{
    auto find = components_.find( ComponentType::getID() );
    if( find == components_.end() ) return nullptr;

    // �Ή�����R���|�[�l���g��ԋp
    return static_cast<ComponentType*>( find->second );
}

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR2D_HEADER_
/// EOF
