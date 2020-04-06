///
/// @file   task.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_TASK_HEADER_
#define INCLUDED_EGEG_TASK_HEADER_

#include <cstdint>
#include <functional>
#include "job.hpp"

BEGIN_EGEG

///
/// @class  Task
/// @brief  タスクマネージャーに登録する単位
///
class Task :
    Job<void(uint64_t)>
{
public :
    using Job<void(uint64_t)>::operator();
    using Job<void(uint64_t)>::setContainer;
    using Job<void(uint64_t)>::exitFromContainer;

    template <class OwnerType>
    void setJob( OwnerType* Owner, void(OwnerType::*Function)(uint64_t) )
    {
        Job<void(uint64_t)>::setJob( std::bind(Function, Owner, std::placeholders::_1) );
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
