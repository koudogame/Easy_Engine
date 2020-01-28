///
/// @file   render_component.hpp
/// @author 板場
///
/// @brief  描画コンポーネント
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#include "component.hpp"
BEGIN_EGEG
class RenderComponent :
    public Component
{
public :
    RenderComponent();
    virtual ~RenderComponent();

    ///
    /// @brief  描画処理
    ///
    virtual void render() = 0;

    ///
    /// @brief   描画ステータス設定
    /// @details 引数に[ true ]を設定した場合、描画されます。
    ///
    /// @param[in] Visible : 可視状態
    ///
    void setVisible( bool Visible );
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
