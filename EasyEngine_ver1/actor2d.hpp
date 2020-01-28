///
/// @file   actor2d.hpp
/// @author 板場
///
/// @brief  アクター2D
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
#include "actor.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class Actor2D :
    public Actor
{
public :
    virtual ~Actor2D() = default;

    ///
    /// @brief  座標のセット
    ///
    /// @param[in] Position : セットする座標
    ///
    virtual void setPosition( const Vector2D& Position ) = 0;
    ///
    /// @brief  現在座標の取得
    ///
    /// @return 現在の座標
    ///
    virtual const Vector2D& getPosition() const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
/// EOF
