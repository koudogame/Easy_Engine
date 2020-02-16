///
/// @file   game_unit.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_GAME_UNIT_HEADER_
#define INCLUDED_EGEG_GAME_UNIT_HEADER_
#include <cstdint>
#include "egeg.hpp"
BEGIN_EGEG
///
/// @class  GameUnit
/// @brief  オブジェクト単位
///
class GameUnit
{
public :
    virtual ~GameUnit() = default;

    ///
    /// @brief  初期化処理
    ///
    /// @return 成功[ true ]　失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了処理
    ///
    virtual void finalize() = 0;
    ///
    /// @brief  更新処理
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時差(ミリ秒)
    ///
    virtual void update( uint64_t DeltaTimeMS ) = 0;
};
END_EGEG
#endif /// INCLUDED_EGEG_GAME_UNIT_HEADER_
/// EOF
