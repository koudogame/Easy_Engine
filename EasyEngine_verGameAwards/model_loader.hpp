///
/// @file   model_loader.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_MODEL_LOADER_HEADER_
#define INCLUDED_EGEG_MODEL_LOADER_HEADER_

#include "rendering_manager_child.hpp"
#include "result.hpp"
#include "mesh.hpp"

BEGIN_EGEG

///
/// @class  ModelLoader
/// @brief  ���f���̃��[�_�[( ���N���X )
///
class ModelLoader :
    public RenderingManagerChild
{
public :
    enum class CoordinateSystem
    {
        kLeftHand,
        kRightHand,
    };

    ///
    /// @brief  ���f���̓ǂݍ���
    ///
    /// @param[in] FilePath         : �ǂݍ��ރt�@�C���̃p�X
    /// @param[in] Output           : ���b�V���f�[�^���o�͂���o�b�t�@
    /// @param[in] CoordinateSystem : ���f���̍��W�n
    ///
    /// @return ���� : true�@���s : false
    ///
    virtual DetailedResult<bool> load(
        const std::string& FilePath,
        Mesh* Output,
        const CoordinateSystem CoordinateSystem
    ) = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_MODEL_LOADER_HEADER_
/// EOF
