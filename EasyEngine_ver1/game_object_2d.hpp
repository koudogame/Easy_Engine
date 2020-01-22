///
/// @file   game_object_2d.hpp
/// @author ��
///
/// @brief  2D�Q�[���I�u�W�F�N�g
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
