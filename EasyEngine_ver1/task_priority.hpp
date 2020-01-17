///
/// @file   task_priority.hpp
/// @author 板場
///
/// @brief  タスクの登録時優先度の定義
///
#ifndef INCLUDED_EGEG_TASK_PRIORITY_HEADER_
#define INCLUDED_EGEG_TASK_PRIORITY_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
///
/// @enum    TaskPriority
/// @details 値の小さい方が先に実行されます。
///
enum TaskPriority : uint32_t
{
    kMoveComponent,
};
#endif /// !INCLUDED_EGEG_TASK_PRIORITY_HEADER_
/// EOF
