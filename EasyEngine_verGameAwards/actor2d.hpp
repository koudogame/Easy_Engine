///
/// @file   actor2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR2D_HEADER_
#define INCLUDED_EGEG_ACTOR2D_HEADER_
#include <cassert>
#include <list>
#include <unordered_map>
#include "actor.hpp"
#include "uid.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class Component;

///
/// @class  Actor2D
/// @brief  2D�A�N�^�[
///
class Actor2D :
    public Actor
{
public :
    ///< �f�X�g���N�^
    virtual ~Actor2D() noexcept
    {
        if( parent_ ) parent_->removeChild( this );
    }

    ///
    /// @brief  ���W�̐ݒ�
    ///
    /// @param[in] Destination : ���W
    ///
    void setPosition( const Vector2D& Destination ) noexcept { position_ = Destination; }
    ///
    /// @brief  ���W�̎擾
    ///
    /// @return ���W
    ///
    const Vector2D& getPosition() const noexcept { return position_; }

    ///
    /// @brief  �e�A�N�^�[�̐ݒ�
    ///
    /// @param[in] Parent : �ݒ肷��e�A�N�^�[
    ///
    void setParent( Actor2D* Parent ) noexcept { parent_ = Parent; }
    ///
    /// @brief  �q�A�N�^�[�̒ǉ�
    ///
    /// @param[in] Child : �ǉ�����q�A�N�^�[
    ///
    void addChild( Actor2D* Child ) noexcept { assert(Child); Child->setParent( this ); childs_.push_back( Child ); }
    ///
    /// @brief  �q�A�N�^�[�̍폜
    ///
    /// @param[in] Child : �폜�Ώۂ̎q�A�N�^�[
    ///
    void removeChild( Actor2D* Child ) noexcept { childs_.remove( Child ); }

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
    Actor2D* parent_ = nullptr;
    std::list<Actor2D*> childs_;

private :
    Vector2D position_{ 0.0F, 0.0F };
    std::unordered_map<uint32_t, Component*> components_;
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
    components_.emplace( UID<ComponentType>(), component );

    return component;
}

///< �R���|�[�l���g�̎擾
template <class ComponentType>
ComponentType* Actor2D::getComponent() const
{
    auto find = components_.find( UID<ComponentType>() );
    if( find == components_.end() ) return nullptr;

    // �Ή�����R���|�[�l���g��ԋp
    return static_cast<ComponentType*>( find->second );
}
END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR2D_HEADER_
/// EOF
