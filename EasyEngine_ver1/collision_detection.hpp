///
/// @file   collision_detection.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
#define INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"
BEGIN_EGEG
///
/// @class  CollisionDetection
/// @brief  �Փ˔���N���X
///
class CollisionDetection
{
public :
    ///
    /// @brief  ��`�Ƌ�`�̏Փ˔���
    ///
    /// @param[in] Rect1 : ��`1
    /// @param[in] Rect2 : ��`2
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Rectangle& Rect1, const Rectangle& Rect2 );
    ///
    /// @brief  �~�`�Ɖ~�`�̏Փ˔���
    ///
    /// @param[in] Circle1 : �~�`1
    /// @param[in] Circle2 : �~�`2
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Circle& Circle1, const Circle& Circle2 );
    ///
    /// @brief  �����Ɛ����̌�������
    ///
    /// @param[in]  Line1 : �����P
    /// @param[in]  Line2 : ����2
    /// @param[out] DivRatio1 : Line1�ɑ΂��������
    /// @param[out] DivRatio2 : Line2�ɑ΂��������
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Line& Line1, const Line& Line2, float* DivRatio1 = nullptr, float* DivRatio2 = nullptr );
    ///
    /// @brief  ��`�Ɖ~�`�̏Փ˔���
    ///
    /// @param[in] Rect   : ��`
    /// @param[in] Circle : �~�`
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Rectangle& Rect, const Circle& Circle );
    static bool isCollided( const Circle& Circle, const Rectangle& Rect ) { return isCollided( Rect, Circle ); }
    ///
    /// @brief  ��`�Ɛ����̏Փ˔���
    ///
    /// @param[in] Rect : ��`
    /// @param[in] Line : ����
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Rectangle& Rect, const Line& Line );
    static bool isCollided( const Line& Line, const Rectangle& Rect ) { return isCollided( Rect, Line ); }
    ///
    /// @brief  �~�`�Ɛ����̏Փ˔���
    ///
    /// @param[in] Circle : �~�`
    /// @param[in] Line   : ����
    ///
    /// @return �Փ˂���[ true ]�@�Փ˂Ȃ�[ false ]
    ///
    static bool isCollided( const Circle& Circle, const Line& Line );
    static bool isCollided( const Line& Line, const Circle& Circle ) { return isCollided( Circle, Line );  }
};
END_EGEG
#endif /// !INCLUDED_EGEG_COLLISION_DETECTION_HEADER_
/// EOF
