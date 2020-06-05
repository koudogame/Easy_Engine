///
/// @file   render_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDER_COMPONENT_HEADER_

#include "component.hpp"
#include "mesh.hpp"
#include "shader.hpp"

BEGIN_EGEG

///
/// @class  RenderComponent
/// @brief  描画コンポーネント
///
class RenderComponent :
    public Component
{
public :
    RenderComponent( LevelNode* Owner ) :
        Component{ Owner } {}

    ///
    /// @brief  メッシュのセット
    ///
    /// @param[in] Mesh : メッシュ
    ///
    void setMesh( const Mesh* Mesh ) noexcept { mesh_ = Mesh; }
    ///
    /// @brief  メッシュの取得
    ///
    /// @return セットされているメッシュ
    ///
    const Mesh* getMesh() const noexcept { return mesh_; }

    ///
    /// @brief  シェーダーのセット
    ///
    /// @param[in] Shader : シェーダー
    ///
    void setShader( const IShader* Shader ) noexcept { shader_ = Shader; }
    ///
    /// @brief  シェーダーの取得
    ///
    /// @return セットされているシェーダー
    ///
    const IShader* getShader() const noexcept { return shader_; }

    ///
    /// @brief  描画状態のセット
    ///
    /// @param[in] State : 状態
    ///
    /// @details true  : 描画を行う  <br>
    ///          false : 描画を行わない
    ///
    void setState( bool State ) noexcept { is_render_ = State; }
    ///
    /// @brief  描画状態の取得
    ///
    /// @return true:描画する　false:描画しない
    ///
    bool getState() const noexcept { return is_render_; }

// override
    bool initialize() override;
    void finalize() override;

private :
    bool is_render_;
    const Mesh* mesh_;
    const IShader* shader_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_RENDER_COMPONENT_HEADER_
/// EOF
