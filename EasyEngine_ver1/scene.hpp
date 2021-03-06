///
/// @file   scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  Scene
///
/// @brief  シーン基底クラス
///
class Scene
{
public :
    virtual ~Scene() = default;

    ///
    /// @brief  シーン初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  シーン終了処理
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間差(:ミリ秒)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;

protected :
    Scene() = default;  ///< 通常ファクトリ以外での生成を禁止しています。
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
