///
/// @file   task_order.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_TASK_ORDER_HEADER_
#define INCLUDED_EGEG_TASK_ORDER_HEADER_

#include <cstdint>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @enum  TaskOrder
/// @brief �^�X�N�D��x
///
/// @details �K�v�Ȏ����R�ɏ��������ĉ������B <br>
///           �G���W�������Ŏg�p����\�����L�邽�߁A0~4�̒l�͎g�p���Ȃ����Ƃ𐄏����܂��B
///           
enum TaskOrder : uint32_t
{
    kActorUpdate = 5U,
    kRender,
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_ORDER_HEADER_
/// EOF
