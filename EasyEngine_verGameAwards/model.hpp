///
/// @file   model.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MODEL_HEADER_
#define INCLUDED_EGEG_MODEL_HEADER_

#include <memory>
#include "mesh.hpp"

BEGIN_EGEG

///
/// @struct Model
/// @brief  ���f�������i�[����\����
///
/// @tparam VertexShaderType   : ���_�V�F�[�_�\�^
/// @tparam GeometryShaderType : �W�I���g���V�F�[�_�[�^
/// @tparam PixelShaderType    : �s�N�Z���V�F�[�_�\�^
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
