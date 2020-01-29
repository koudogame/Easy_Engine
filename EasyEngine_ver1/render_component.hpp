///
/// @file   render_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#include "component.hpp"
#include "render_batch.hpp"
BEGIN_EGEG
///
/// @class   RenderComponent
///          
/// @brief   レンダーコンポーネント
/// @details 描画機能を持ちます。<br>
///          生成と同時にRenderBatchクラスへの登録が行われます。
///
class RenderComponent :
    public Component
{
public :
    RenderComponent( Actor* Owner ) :
        Component( Owner )
    {
        RenderBatch::instance()->registerComponent( this );
    }
    virtual ~RenderComponent()
    {
        RenderBatch::instance()->unregisterComponent( this );
    }

    ///
    /// @brief   描画処理
    /// @details RenderBatchクラスで呼び出されます。
    ///
    virtual void render() = 0;

    ///
    /// @brief  可視状態のセット
    ///
    /// @param[in] State : 設定する可視状態
    ///
    void setVisibleState( bool State ) { is_visible_ = State; }
    ///
    /// @brief  可視状態の取得
    ///
    /// @return 可視状態
    ///
    bool getVisibleState() const { return is_visible_; }

protected :
    bool is_visible_ = false;   ///< 可視状態フラグ
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
