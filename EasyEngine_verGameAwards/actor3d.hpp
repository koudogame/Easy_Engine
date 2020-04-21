///
/// @file   actor3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR3D_HEADER_
#define INCLUDED_EGEG_ACTOR3D_HEADER_

#include <cassert>
#include "actor.hpp"
#include "type_id.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  Actor3D
/// @brief  3D�A�N�^�[
///
class Actor3D :
    public Actor
{
public :
    ///
    /// @brief  �R���|�[�l���g�̒ǉ�
    ///
    /// @tparam ComponentType : �ǉ�����R���|�[�l���g�^
    ///
    /// @return �ǉ������R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* addComponent();

protected :
    Actor3D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}
};

///< �R���|�[�l���g�̒ǉ�
template <class ComponentType>
ComponentType* Actor3D::addComponent()
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

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR3D_HEADER_
/// EOF
