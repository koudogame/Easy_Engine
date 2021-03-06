///
/// @file   renderin3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING3D_COMPONENT_HEADER_
#define INCLUDED_EGEG_RENDERING3D_COMPONENT_HEADER_

#include "component3d.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"

BEGIN_EGEG
namespace component {

///
/// @class  Rendering3D
/// @brief  描画コンポ―ネント
///
class Rendering3D :
    public Component3D
{
public :
    static uint32_t getID() noexcept { return ComponentID::kRendering3D; }

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
    
    ///< メッシュのセット
    void setMesh( const Mesh* Mesh ) noexcept { mesh_data_ = Mesh; }
    ///< 頂点シェーダーのセット
    void setVertexShader( VertexShader* Shader ) noexcept { vertex_shader_ = Shader; }
    ///< ジオメトリーシェーダーのセット
    void setGeometryShader( GeometryShader* Shader ) noexcept { geometry_shader_ = Shader; }
    ///< ピクセルシェーダーのセット
    void setPixelShader( PixelShader* Shader ) noexcept { pixel_shader_ = Shader; }

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
