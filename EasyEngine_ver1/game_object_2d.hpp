///
/// @file   game_object_2d.hpp
/// @author 板場
///
/// @brief  2Dゲームオブジェクト
///
#ifndef INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
#define INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
#include "game_object.hpp"
#include "egeg_math.hpp"
BEGIN_EGEG
class GameObject2D :
    public GameObject
{
public :
    virtual ~GameObject2D() = default;

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
