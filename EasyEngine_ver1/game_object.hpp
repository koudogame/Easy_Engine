///
/// @file   game_object.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class  GameObject
/// @brief  ゲーム上のオブジェクトの基底クラス
///
class GameObject
{
public :
    virtual ~GameObject() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @return 初期化成功[ true ]　初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;

    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差(: ミリ秒)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_HEADER_
/// EOF
