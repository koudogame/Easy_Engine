///
/// @file   model.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MODEL_HEADER_
#define INCLUDED_EGEG_MODEL_HEADER_
#include "mesh.hpp"
#include "texture.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
BEGIN_EGEG
///
/// @struct Model
///
/// @brief  モデル
///
struct Model
{
    Mesh             mesh;              ///< メッシュ
    ITexture*        texture;           ///< テクスチャ
    IVertexShader*   vertex_shader;     ///< 頂点シェーダー
    IGeometryShader* geometry_shader;   ///< ジオメトリシェーダー
    IPixelShader*    pixel_shader;      ///< ピクセルシェーダー
};
END_EGEG
#endif /// !INCLUDED_EGEG_MODEL_HEADER_
/// EOF
