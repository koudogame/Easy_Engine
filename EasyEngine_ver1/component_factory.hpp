///
/// @file   component_factory.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
#define INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
#include "factory.hpp"
#include "component.hpp"
BEGIN_EGEG
///
/// @class   ComponentFactory
///          
/// @brief   コンポーネントファクトリ
/// @details シングルトンクラスです。アクセスにはinstance関数を使用して下さい。
///
class ComponentFactory :
    public Factory<Component, Component*(*)(Actor*), Actor*>
{
public :
    ///
    /// @brief  インスタンスの取得
    ///
    /// @return インスタンス
    ///
    static ComponentFactory* instance() { static ComponentFactory i; return &i; }

private :
    ComponentFactory() = default;
    ComponentFactory( const ComponentFactory& ) = delete;
    ComponentFactory& operator=( const ComponentFactory& ) = delete;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_FACTORY_HEADER_
/// EOF
