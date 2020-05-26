///
/// @file   model_loader.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_MODEL_LOADER_HEADER_
#define INCLUDED_EGEG_MODEL_LOADER_HEADER_

#include "rendering_manager_child.hpp"
#include "return_value.hpp"
#include "mesh.hpp"

BEGIN_EGEG

///
/// @class ModelLoader
/// @brief モデルローダー
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
    /// @brief モデルの読み込み
    ///
    /// @param[in] ModelFilePath    : 読み込むファイルのパス
    /// @param[in] CoordinateSystem : モデルデータの座標系
    /// @param[out] MeshOut         : メッシュデータの出力先
    ///
    /// @return true:成功　false:失敗
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
