///
/// @file   collision_section.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_COLLISION_SECTION_HEADER_
#define INCLUDED_EGEG_COLLISION_SECTION_HEADER_
#include <list>
#include "collision_component.hpp"
BEGIN_EGEG
///
/// @class  CollisionSection
/// @brief  空間のセクション
///
class CollisionSection
{
public :
    ///
    /// @brief  衝突コンポーネントの追加
    ///
    /// @param[in] pComponent : 追加するコンポーネント
    ///
    void entry( CollisionComponent* pComponent );
    ///
    /// @brief   衝突コンポーネントの削除
    /// @details コンポーネントの所属セクションを解除しています。<br>
    ///          セクションの移動は 1.exit - 2.entry の順番で行ってください。
    ///
    /// @param[in] pComponent : 削除するコンポーネント
    ///
    void exit( CollisionComponent* pComponent );

    ///
    /// @brief   現在指している子セクションの選択
    /// @details 保持しているセクションを呼び出し毎に返却します。<br>
    ///          一巡した場合、最後にnullptrを返却します。
    ///
    /// @return  子セクション
    ///
    CollisionSection* pickChild();

    ///
    /// @brief   現在指しているコンポーネントの選択
    /// @details 保持しているコンポーネントを呼び出し毎に返却します。<br>
    ///          一巡した場合、最後にnullptrを返却します。
    ///
    /// @return  コンポーネント
    ///
    CollisionComponent* pickComponent();

private :
    std::vector<CollisionSection*> childs_;
    std::list<CollisionComponent*> components_;

    uint32_t child_idx_  = 0U;
    std::list<CollisionComponent*>::iterator component_itr_ = components_.begin();
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_SECTION_HEADER_
/// EOF
