///
/// @file   model_loader.hpp
/// @author ��
/// 
#ifndef INCLUDED_EGEG_MODEL_LOADER_HEADER_
#define INCLUDED_EGEG_MODEL_LOADER_HEADER_

#include "rendering_manager_child.hpp"
#include "return_value.hpp"
#include "mesh.hpp"

BEGIN_EGEG

///
/// @class ModelLoader
/// @brief ���f�����[�_�[
///
class ModelLoader :
    public RenderingManagerChild
{
public :
    enum class CoordinateSystem
    {
        kLeftHand,
        kRightHand
    };

    ///
    /// @brief ���f���̓ǂݍ���
    ///
    /// @param[in] ModelFilePath    : �ǂݍ��ރt�@�C���̃p�X
    /// @param[in] CoordinateSystem : ���f���f�[�^�̍��W�n
    /// @param[out] MeshOut         : ���b�V���f�[�^�̏o�͐�
    ///
    /// @return true:�����@false:���s
    ///
    virtual DetailedReturnValue<bool> load(
        const std::string& ModelFilePath,
        CoordinateSystem CoordinateSystem,
        Mesh* MeshOut
    ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MODEL_LOADER_HEADER_
/// EOF
