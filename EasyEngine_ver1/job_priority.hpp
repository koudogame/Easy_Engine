///
/// @file   job_priority.hpp
/// @author 板場
///
/// @brief  ジョブの登録時優先度の定義
///
#ifndef INCLUDED_EGEG_JOB_PRIORITY_HEADER_
#define INCLUDED_EGEG_JOB_PRIORITY_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
///
/// @enum    JobPriority
/// @details 値の小さい方が先に実行されます。
///
enum JobPriority : uint32_t
{
    kMoveComponent,
    kSceneManager,
};
#endif /// !INCLUDED_EGEG_JOB_PRIORITY_HEADER_
/// EOF
