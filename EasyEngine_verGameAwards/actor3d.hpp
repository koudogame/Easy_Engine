///
/// @file   actor3d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR3D_HEADER_
#define INCLUDED_EGEG_ACTOR3D_HEADER_
#include <cassert>
#include <unordered_map>
#include "actor.hpp"
#include "uid.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class Component;

///
/// @class  Actor3D
/// @brief  3D�A�N�^�[
///
class Actor3D :
    public Actor
{
public :
    ///
    /// @brief  ���W�̐ݒ�
    ///
    /// @param[in] Destination : ���W
    ///
    void setPosition( const Vector3D& Destination ) noexcept { position_ = Destination; }
    ///
    /// @brief  ���W�̎擾
    ///
    /// @return ���W
    ///
    const Vector3D& getPosition() const noexcept { return position_; }

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
    /// @details �Ή�����R���|�[�l���g���Ȃ��ꍇ�Anullptr��ԋp���܂��B
    ///
    /// @tparam ComponentType : �擾����R���|�[�l���g�^
    ///
    /// @return �R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* getComponent() const;

protected :
    Actor3D( uint32_t ActorID ) noexcept : Actor( ActorID ) {}

private :
    Vector3D position_;
    std::unordered_map<uint32_t, Component*> components_;
};

///< �R���|�[�l���g�̒ǉ�
template <class ComponentType>
ComponentType* Actor3D::addComponent()
{
    assert( getComponent<ComponentType>() == nullptr &&
        "�R���|�[�l���g�̑��d�o�^�����o���܂����B" );

    // �R���|�[�l���g�̐���
    ComponentType component = new ComponentType( this );
    component->initialize();

    // ���������R���|�[�l���g�����X�g�ɒǉ�
    components_.emplace( UID<ComponentType>(), component );

    return component;
}

///< �R���|�[�l���g�̎擾
template <class ComponentType>
ComponentType* Actor3D::getComponent() const
{
    auto find = components_.find( UID<ComponentType>() );
    if( find == components_.end() ) return nullptr;

    // �Ή�����R���|�[�l���g�̕ԋp
    return static_cast<ComponentType*>( find->second );
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR3D_HEADER_
/// EOF
