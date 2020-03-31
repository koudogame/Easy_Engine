///
/// @file   renderin3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING3D_COMPONENT3D_HEADER_
#define INCLUDED_EGEG_RENDERING3D_COMPONENT3D_HEADER_
#include "component3d.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "actor3d.hpp"
BEGIN_EGEG
namespace component {
///
/// @class  Rendering
/// @brief  描画コンポ―ネント
///
class Rendering3D :
    public Component3D
{
public :
    static constexpr UID<Rendering3D> getID() noexcept { return UID<Rendering3D>(); }

    Rendering3D( Actor3D* Owner ) :
        Component3D( Owner )
    {}

    ///
    /// @brief  モデル情報のセット
    ///
    /// @param[in] Model : セットするモデル
    ///
    template <class ModelType>
    void setModel( ModelType& Model )
    {
        mesh_data_ = &Model.mesh;
        vertex_shader_ = Model.vertex_shader.get();
        geometry_shader_ = Model.geometry_shader.get();
        pixel_shader_ = Model.pixel_shader.get();
    }

    ///< メッシュデータの取得
    const Mesh* getMesh() const noexcept { return mesh_data_; }
    ///< 頂点シェーダーの取得
    VertexShader* getVertexShader() const noexcept { return vertex_shader_; }
    ///< ジオメトリシェーダ―の取得
    GeometryShader* getGeometryShader() const noexcept { return geometry_shader_; }
    ///< ピクセルシェーダ―の取得
    PixelShader* getPixelShader() const noexcept { return pixel_shader_; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize()   override;
/*-----------------------------------------------------------------*/
private :
    const Mesh*   mesh_data_ = nullptr;
    VertexShader* vertex_shader_ = nullptr;
    GeometryShader* geometry_shader_ = nullptr;
    PixelShader* pixel_shader_ = nullptr;
};
} /// namespace component
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING3D_COMPONENT_HEADER_
/// EOF
