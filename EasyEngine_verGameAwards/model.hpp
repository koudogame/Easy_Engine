///
/// @file   model.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MODEL_HEADER_
#define INCLUDED_EGEG_MODEL_HEADER_

#include <memory>
#include "mesh.hpp"

BEGIN_EGEG

///
/// @struct Model
/// @brief  モデル情報を格納する構造体
///
/// @tparam VertexShaderType   : 頂点シェーダ―型
/// @tparam GeometryShaderType : ジオメトリシェーダー型
/// @tparam PixelShaderType    : ピクセルシェーダ―型
///
template <
    class VertexShaderType,
    class GeometryShaderType,
    class PixelShaderType >
struct Model
{
    Mesh mesh;
    std::unique_ptr<VertexShaderType> vertex_shader;
    std::unique_ptr<GeometryShaderType> geometry_shader;
    std::unique_ptr<PixelShaderType> pixel_shader;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MODEL_HEADER_
/// EOF
