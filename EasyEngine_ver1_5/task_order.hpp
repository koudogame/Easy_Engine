///
/// @file   task_order.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TASK_ORDER_HEADER_
#define INCLUDED_EGEG_TASK_ORDER_HEADER_

#include <cstdint>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @enum  TaskOrder
/// @brief タスク優先度
///
/// @brief エンジン内で使用しているタスク優先順位です。
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
