///
/// @file   level_light.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_LEVEL_LIGHT_HEADER_
#define INCLUDED_EGEG_LEVEL_LIGHT_HEADER_

#include "level_node.hpp"
#include "egeg_math.hpp"

BEGIN_EGEG

///
/// @class  LevelLight
/// @brief  レベルノード「ライト」
///
/// @details ライトです。ゲーム中に出てくるライト関係のオブジェクトはこのクラスを継承してください。
///
class LevelLight :
    public LevelNode
{
public :
    enum class LightType
    {
        kDirectional,
        kPoint
    };

    static constexpr NodeType kNodeType = NodeType::kLight;
    NodeType getNodeType() const noexcept { return kNodeType; }

    ///
    /// @brief  ライト型を取得
    ///
    /// @return ライト型
    ///
    virtual LightType getLightType() = 0;

    ///
    /// @brief  ビュー座標変換行列を計算
    ///
    /// @return ライトの視点への変換行列
    ///
    virtual Matrix4x4 calcViewMatrix() const = 0;
};

END_EGEG
#endif /// !INCLUDED_EGEG_LEVEL_LIGHT_HEADER_
/// EOF
