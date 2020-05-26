///
/// @file   actor2d.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_ACTOR2D_HEADER_
#define INCLUDED_EGEG_ACTOR2D_HEADER_

#ifdef _DEBUG
#include <cassert>
#endif
#include "actor.hpp"

BEGIN_EGEG

///
/// @class Actor2D
/// @brief 2D�A�N�^�[
///
class Actor2D :
    public Actor
{
public :
    virtual ~Actor2D() = default;

    ///
    /// @brief �R���|�[�l���g�̒ǉ�
    ///
    /// @tparam ComponentType : �ǉ�����R���|�[�l���g�̌^
    ///
    /// @return �ǉ������R���|�[�l���g
    ///
    template <class ComponentType>
    ComponentType* addComponent();

// override
    DirectX::XMMATRIX calcWorldMatrix() const override;
protected :
    explicit Actor2D( uint32_t ID ) noexcept : Actor{ID} {}
};


///< �R���|�[�l���g�̒ǉ��֐���`
template <class ComponentType>
ComponentType* Actor2D::addComponent()
{
#ifdef _DEBUG
    assert( getComponent<ComponentType>() == nullptr &&
            "�R���|�[�l���g�̑��d�o�^�͂ł��܂���B" );
#endif
    auto component = std::unique_ptr<ComponentType, ComponentDeleter>
        { new ComponentType{this}, ComponentDeleter{} };
    if( !component->initialize() ) return nullptr;

    ComponentType* ptr = component.get();
    components_.emplace( TypeID<ComponentType>{}, std::move(component) );

    return ptr;
}

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR2D_HEADER_
/// EOF
///