///
/// @file   job_priority.hpp
/// @author ��
///
/// @brief  �W���u�̓o�^���D��x�̒�`
///
#ifndef INCLUDED_EGEG_JOB_PRIORITY_HEADER_
#define INCLUDED_EGEG_JOB_PRIORITY_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
///
/// @enum    JobPriority
/// @details �l�̏�����������Ɏ��s����܂��B
///
enum JobPriority : uint32_t
{
    kMoveComponent,
    kSceneManager,
};
#endif /// !INCLUDED_EGEG_JOB_PRIORITY_HEADER_
/// EOF
