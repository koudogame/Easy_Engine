///
/// @file    body_2d.hpp
/// @author  ��
///          
/// @brief   �{�f�B
/// @details �Փ˔���̏������u�_�u���f�B�X�p�b�`�v���g�p���Ď������Ă��܂��B
///
#ifndef INCLUDED_EGEG_BODY_2D_HEADER_
#define INCLUDED_EGEG_BODY_2D_HEADER_
#include "point_2d.hpp"
#include "circle_2d.hpp"
#include "line_2d.hpp"
BEGIN_EGEG
class IBody2D
{
public :
    virtual ~IBody2D() = default;

    ///
    /// @brief  ��Έړ�
    ///
    /// @param[in] Destination : �ړ���̍��W
    ///
    virtual void moveAbs( const Vector2D& Destination ) = 0;
    ///
    /// @brief  ���Έړ�
    ///
    /// @param[in] Distance : �ړ�����
    ///
    virtual void moveRel( const Vector2D& Distance ) = 0;

    ///
    /// @brief   �_�u���f�B�X�p�b�`�J�n���b�Z�[�W
    /// @details ����Ɏ����̏ڍׂȌ`��`���A�Փ˂̔�����s���Ă��炢�܂��B
    ///          ex.) Body->isCollision( this->shape_ );    �̂悤�Ɏ������Ă��������B
    ///
    /// @param[in] Body : �Փ˂𔻒肷�鑊��
    ///
    virtual bool isCollision( const IBody2D* Body ) const = 0;

    ///
    /// @brief  �_�Ƃ̏Փ˔���
    ///
    /// @param[in] Point : �Փ˂𔻒肷��_
    ///
    /// @return �Փ˂���[ true ] �Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Point2D& Point ) = 0;
    ///
    /// @brief  �~�Ƃ̏Փ˔���
    ///
    /// @param[in] Circle : �Փ˂𔻒肷��~
    ///
    /// @return �Փ˂���[ true ] �Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Circle& Circle ) = 0;
    ///
    /// @brief  �����Ƃ̏Փ˔���
    ///
    /// @param[in] Line : �Փ˂𔻒肷�����
    ///
    /// @return �Փ˂���[ true ] �Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Line2D& Line ) = 0;

    ///
    /// @brief   ��̂̏Փ˔͈͂��擾
    /// @details �ڍׂȏՓ˔�����s���O�̃e�X�g
    ///
    /// @return  ��͈̂̔�( Circle )
    ///
    virtual const Circle& getRoughRange() const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_BODY_2D_HEADER_
/// EOF
