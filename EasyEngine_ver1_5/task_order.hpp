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
/// @brief �G���W�����Ŏg�p���Ă���^�X�N�D�揇�ʂł��B
///           
enum TaskOrder : uint32_t
{
    kInputDeviceUpdate,
    kLevelUpdate,
    kRendering,
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_ORDER_HEADER_
/// EOF
