///
/// @file   actor2d.hpp
/// @author ��
///
/// @brief  �A�N�^�[2D
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
    /// @brief  ���W�̃Z�b�g
    ///
    /// @param[in] Position : �Z�b�g������W
    ///
    virtual void setPosition( const Vector2D& Position ) = 0;
    ///
    /// @brief  ���ݍ��W�̎擾
    ///
    /// @return ���݂̍��W
    ///
    virtual const Vector2D& getPosition() const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_GAME_OBJECT_2D_HEADER_
/// EOF
