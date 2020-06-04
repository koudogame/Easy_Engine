///
/// @file   level_camera.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_CAMERA_HEADER_
#define INCLUDED_EGEG_LEVEL_CAMERA_HEADER_

#include "level_node.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  LevelCamera
/// @brief  レベルノード「カメラ」
///
/// @details カメラです。ゲーム中の視点を操作するオブジェクトはこのクラスを継承してください。
///
class LevelCamera :
    public LevelNode
{
public :
    static constexpr NodeType kNodeType = NodeType::kCamera;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  ビュー座標変換行列を計算
    ///
    /// @return ビュー座標変換行列
    ///
    virtual Matrix4x4 calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_CAMERA_HEADER_
/// EOF
