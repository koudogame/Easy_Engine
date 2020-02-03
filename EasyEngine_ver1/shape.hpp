///
/// @file   shape.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_SHAPE_HEADER_
#define INCLUDED_EGEG_SHAPE_HEADER_
#include "egeg_math.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"
BEGIN_EGEG
///
/// @class  Shape
/// @brief  �`���N���X
///
/// @details �Փ˔�����s���`�N���X�̊��N���X�ł��B<br>
///          �Փ˔���̓_�u���f�B�X�p�b�`�𗘗p���Ď������Ă��܂��B
///
class Shape
{
public :
    virtual ~Shape() = default;

    ///
    /// @brief   �Փ˔���t�@�[�X�g�f�B�X�p�b�`
    /// @details ����̎��g�̌`�Ƃ̏Փ˔��菈�����Ăяo���܂��B
    ///
    /// @param[in] Other : �Փ˂𔻒肷�鑊��
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( Shape* Other ) const = 0;
    ///
    /// @brief  ��`�Ƃ̏Փ˔���
    ///
    /// @param[in] Rectangle : �Փ˂𔻒肷���`
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Rectangle& Rectangle ) const = 0;
    ///
    /// @brief  �~�`�Ƃ̏Փ˔���
    ///
    /// @param[in] Circle : �Փ˂𔻒肷��~�`
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Circle& Circle ) const = 0;
    ///
    /// @brief  �����Ƃ̏Փ˔���
    ///
    /// @param[in] Line : �Փ˂𔻒肷�����
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    virtual bool isCollision( const Line& Line ) const = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SHAPE_HEADER_
/// EOF
