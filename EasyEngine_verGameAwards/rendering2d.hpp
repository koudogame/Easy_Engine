///
/// @file   rendering2d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_

#include <wrl.h>
#include <d3d11.h>
#include "component2d.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"

BEGIN_EGEG
namespace component
{

///
/// @class  Rendering2D
/// @brief  描画コンポーネント
///
class Rendering2D :
    public Component2D
{
public :
    static constexpr TypeID<Rendering2D> getID() noexcept { return TypeID<Rendering2D>(); }

    Rendering2D( Actor2D* Owner ) :
        Component2D( Owner )
    {}
    
    ///
    /// @brief  テクスチャのセット
    ///
    /// @param[in] ShaderResourceView : テクスチャへのビュー
    ///
    template <class ViewPtr>
    void setTexture( ViewPtr&& ShaderResourceView ) noexcept
    {
        texture_ = std::forward<ViewPtr>( ShaderResourceView );
    }
    ///
    /// @brief  テクスチャの取得
    ///
    /// @return テクスチャへのビュー
    ///
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> getTexture() const noexcept 
    {
        return texture_; 
    }

    ///
    /// @brief  切り取り範囲のセット
    /// @brief  左上を{ x: 0, y: 0 } とし、ピクセル単位で指定して下さい。
    ///
    /// @param[in] Range : 切り取り範囲
    ///
    void setTrimmingRange( const D3D11_RECT& Range ) noexcept
    {
        trimming_range_ = Range;
    }
    ///
    /// @brief  切り取り範囲の取得
    ///
    /// @return 切り取り範囲
    ///
    const D3D11_RECT& getTrimmingRange() const noexcept
    {
        return trimming_range_;
    }

    ///
    /// @brief  頂点シェーダ―のセット
    ///
    /// @param[in] Shader : セットするシェーダー
    ///
    void setVertexShader( VertexShader* Shader ) noexcept { vertex_shader_ = Shader; }
    ///
    /// @brief  頂点シェーダ―の取得
    ///
    /// @return 頂点シェーダ―
    ///
    VertexShader* getVertexShader() const noexcept { return vertex_shader_; }

    ///
    /// @brief  ジオメトリシェーダーのセット
    ///
    /// @param[in] Shader : セットするシェーダー
    ///
    void setGeometryShader( GeometryShader* Shader ) noexcept { geometry_shader_ = Shader; }
    ///
    /// @brief  ジオメトリシェーダーの取得
    ///
    /// @return ジオメトリシェーダー
    ///
    GeometryShader* getGeometryShader() const noexcept { return geometry_shader_; }

    ///
    /// @brief  ピクセルシェーダ―のセット
    ///
    /// @param[in] Shader : セットするシェーダー
    ///
    void setPixelShader( PixelShader* Shader ) noexcept { pixel_shader_ = Shader; }
    ///
    /// @brief  ピクセルシェーダ―の取得
    ///
    /// @return ピクセルシェーダ―
    ///
    PixelShader* getPixelShader() const noexcept { return pixel_shader_; }

/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize()   override;
/*-----------------------------------------------------------------*/
private :
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
    D3D11_RECT trimming_range_;
    VertexShader* vertex_shader_     = nullptr;
    GeometryShader* geometry_shader_ = nullptr;
    PixelShader* pixel_shader_       = nullptr;
};

} // namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING2D_COMPONENT_HEADER_
/// EOF
