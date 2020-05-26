///
/// @file   rendering_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_

#include "component.hpp"
#include "mesh.hpp"
#include "scene.hpp"

BEGIN_EGEG

///
/// @class RenderingComponent
/// @brief 描画コンポーネント
///
class RenderingComponent :
    public Component
{
public :
    RenderingComponent( Actor* Owner ) :
        affiliation_scene_{ nullptr },
        Component{ Owner },
        state_{ true }
    {}

    ///
    /// @brief メッシュのセット
    ///
    /// @param[in] Mesh : メッシュ
    ///
    /// @details 引数のMeshは保持するシェーダーの所有者を移すため、右辺値参照で渡してください。
    ///
    void setMesh( const Mesh& Mesh ) noexcept { mesh_ = &Mesh; }
    /// @brief  メッシュの取得
    ///
    /// @return メッシュ
    ///
    const Mesh& getMesh() const noexcept { return *mesh_; }

    ///
    /// @brief     描画状態のセット
    ///
    /// @param[in] State : セットする状態
    ///
    /// @details   true:描画する　false:描画しない
    ///
    void setState( bool State ) noexcept { state_ = State; }
    ///
    /// @brief 描画状態の取得
    ///
    /// @return true:描画する　false:描画しない
    ///
    bool getState() const noexcept { return state_; }

// override
    bool initialize() override;
    void finalize() override;
private :
    Scene* affiliation_scene_;
    bool state_;
    const Mesh* mesh_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING_COMPONENT_HEADER_
/// EOF
