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
/// @details 必要な時自由に書き換えて下さい。 <br>
///           エンジン部分で使用する可能性が有るため、0~4の値は使用しないことを推奨します。
///           
enum TaskOrder : uint32_t
{
    kActorUpdate = 5U,
    kRender,
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_ORDER_HEADER_
/// EOF
