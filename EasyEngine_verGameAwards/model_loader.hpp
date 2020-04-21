///
/// @file   model_loader.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_MODEL_LOADER_HEADER_
#define INCLUDED_EGEG_MODEL_LOADER_HEADER_

#include "rendering_manager_child.hpp"
#include "result.hpp"
#include "mesh.hpp"

BEGIN_EGEG

///
/// @class  ModelLoader
/// @brief  モデルのローダー( 基底クラス )
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
    /// @brief  モデルの読み込み
    ///
    /// @param[in] FilePath         : 読み込むファイルのパス
    /// @param[in] Output           : メッシュデータを出力するバッファ
    /// @param[in] CoordinateSystem : モデルの座標系
    ///
    /// @return 成功 : true　失敗 : false
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
