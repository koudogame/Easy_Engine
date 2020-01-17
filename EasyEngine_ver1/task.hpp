///
/// @file    task.hpp
/// @author  板場
///          
/// @brief   タスク単位
/// @details TaskManagerに登録される最小単位です。<br>
///          TaskContainerにより保持されます。
///
#ifndef INCLUDED_EGEG_TASK_HEADER_
#define INCLUDED_EGEG_TASK_HEADER_
#include <cstdint>
#include <functional>
#include "egeg_common.hpp"
BEGIN_EGEG
class TaskContainer;
class Task
{
public :
    ///
    /// @brief  タスクとして実行する関数のセット
    ///
    /// @tparam Object : タスクの保持者の型( 省略可 )
    ///
    /// @param[in] pOwner : タスクの保持者
    /// @param[in] pFunction : セットする関数のアドレス
    ///
    template <typename Object>
    void setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) );

    ///
    /// @brief  コンテナのセット
    ///
    /// @param[in] pContainer : 自信を保持するコンテナ
    ///
    void setContainer( TaskContainer* pContainer ) { p_container_ = pContainer; }
    ///
    /// @brief  コンテナの取得
    ///
    /// @return 自信を保持しているコンテナ
    ///
    TaskContainer* getContainer() const { return p_container_; }

    ///
    /// @brief  セットされているタスクの実行
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差(: ミリ秒)
    ///
    void operator()( uint64_t DeltaTimeMS ) { if( f_task_ ) f_task_( DeltaTimeMS ); }

private :
    TaskContainer* p_container_ = nullptr;  /// 自信を保持しているコンテナ
    std::function<void(uint64_t)> f_task_;  /// セットされているタスク
};

///< Task : タスクのセット
template <typename Object>
void Task::setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) )
{
    f_task_ = std::bind(
        pFunction,
        pOwner,
        std::placeholders::_1 );
}
END_EGEG
#endif /// !INCLUDED_EGEG_TASK_HEADER_
/// EOF
