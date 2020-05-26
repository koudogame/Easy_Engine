///
/// @file   actor3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_ACTOR3D_HEADER_
#define INCLUDED_EGEG_ACTOR3D_HEADER_

#ifdef _DEBUG
#include <cassert>
#endif
#include "actor.hpp"

BEGIN_EGEG

///
/// @class Actor3D
/// @brief 3Dアクター
///
class Actor3D :
    public Actor
{
public :
    virtual ~Actor3D() = default;

    ///
    /// @brief コンポーネントの追加
    ///
    /// @tparam ComponentType : 追加するコンポーネントの型
    ///
    /// @return 追加したコンポーネント
    ///
    template <class ComponentType>
    ComponentType* addComponent();

// override
    DirectX::XMMATRIX calcWorldMatrix() const override;

protected :
    explicit Actor3D( uint32_t ID ) noexcept : Actor{ID} {}
};


///< コンポーネントの追加関数定義
template <class ComponentType>
ComponentType* Actor3D::addComponent()
{
#ifdef _DEBUG
    assert( getComponent<ComponentType>() == nullptr &&
            "コンポーネントの多重登録はできません。" );
#endif
    auto component = std::unique_ptr<ComponentType, ComponentDeleter>
        { new ComponentType{this}, ComponentDeleter{} };
    if( !component->initialize() ) return nullptr;

    ComponentType* ptr = component.get();
    components_.emplace( TypeID<ComponentType>{}, std::move(component) );

    return ptr;
}

END_EGEG
#endif /// !INCLUDED_EGEG_ACTOR3D_HEADER_
/// EOF
