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
    protected Job<void(uint64_t)>
{
public :
    using Job::operator();
    using Job::setContainer;
    using Job::exitFromContainer;

    ///
    /// @brief   ジョブとして実行する関数のセット
    /// @details ex.) .setJob( this, &Hoge::update );   <br>
    ///          セットする関数は、                     <br>
    ///            「メンバ関数」                       <br>
    ///            「戻り値void」                       <br>
    ///            「引数uint64_t」                     <br>
    ///          という要件を満たしてください。
    ///
    /// @param[in] Owner    : 関数の実行者
    /// @param[in] Function : 実行する関数( メンバ関数 )
    ///
    template <class OwnerType>
    void setJob( OwnerType* Owner, void(OwnerType::*Function)(uint64_t) )
    {
        Job::setJob( std::bind(Function, Owner, std::placeholders::_1) );
    }

    Job* operator&() { return this; }
};

END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
