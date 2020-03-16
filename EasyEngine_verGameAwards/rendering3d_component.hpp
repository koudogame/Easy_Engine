///
/// @file   rendering3d_component.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERING3D_COMPONENT3D_HEADER_
#define INCLUDED_EGEG_RENDERING3D_COMPONENT3D_HEADER_
#include "component.hpp"
#include "model.hpp"
#include "vertex_data.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "actor3d.hpp"
BEGIN_EGEG
///
/// @class  RenderingComponent
/// @brief  描画コンポ―ネント
///
class Rendering3DComponent :
    public Component
{
public :
    static uint32_t getID() noexcept { return UID<Rendering3DComponent>(); }

    Rendering3DComponent( Actor3D* Owner ) :
        Component( Owner )
    {}

    template <class ModelType>
    void setModel( ModelType& Model )
    {
        vertex_data_ = &Model.vertex_data;
        vertex_shader_ = Model.vertex_shader.get();
        geometry_shader_ = Model.geometry_shader.get();
        pixel_shader_ = Model.pixel_shader.get();
    }

    VertexData* getVertexData() const noexcept { return vertex_data_; }
    VertexShader* getVertexShader() const noexcept { return vertex_shader_; }
    GeometryShader* getGeometryShader() const noexcept { return geometry_shader_; }
    PixelShader* getPixelShader() const noexcept { return pixel_shader_; }
        
/*-----------------------------------------------------------------*/
// Component
    bool initialize() override;
    void finalize()   override;
/*-----------------------------------------------------------------*/
private :
    VertexData*   vertex_data_ = nullptr;
    VertexShader* vertex_shader_ = nullptr;
    GeometryShader* geometry_shader_ = nullptr;
    PixelShader* pixel_shader_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERING3D_COMPONENT_HEADER_
/// EOF
