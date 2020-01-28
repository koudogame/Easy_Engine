///
/// @file   model.hpp
/// @author ��
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
/// @brief  ���f��
///
struct Model
{
    Mesh             mesh;              ///< ���b�V��
    ITexture*        texture;           ///< �e�N�X�`��
    IVertexShader*   vertex_shader;     ///< ���_�V�F�[�_�[
    IGeometryShader* geometry_shader;   ///< �W�I���g���V�F�[�_�[
    IPixelShader*    pixel_shader;      ///< �s�N�Z���V�F�[�_�[
};
END_EGEG
#endif /// !INCLUDED_EGEG_MODEL_HEADER_
/// EOF
