///
/// @file    job.hpp
/// @author  板場
///
#ifndef INCLUDED_EGEG_JOB_HEADER_
#define INCLUDED_EGEG_JOB_HEADER_
#include <cstdint>
#include <functional>
#include "egeg_common.hpp"
BEGIN_EGEG
class JobContainer;
///
/// @class  Job
///          
/// @brief   ジョブ最小単位
/// @details JobSchedulerに登録される最小単位です。<br>
///          JobContainerにより保持されます。
///
class Job
{
public :
    ///
    /// @brief  ジョブとして実行する関数のセット
    ///
    /// @tparam Object : ジョブの保持者の型( 省略可 )
    ///
    /// @param[in] pOwner : ジョブの保持者
    /// @param[in] pFunction : セットする関数のアドレス
    ///
    template <typename Object>
    void setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) );

    ///
    /// @brief  コンテナのセット
    ///
    /// @param[in] pContainer : 自信を保持するコンテナ
    ///
    void setContainer( JobContainer* pContainer ) { p_container_ = pContainer; }
    ///
    /// @brief  コンテナの取得
    ///
    /// @return 自信を保持しているコンテナ
    ///
    JobContainer* getContainer() const { return p_container_; }

    ///
    /// @brief  セットされているジョブの実行
    ///
    /// @param[in] DeltaTimeMS : 前回呼び出し時からの時間の差(: ミリ秒)
    ///
    void operator()( uint64_t DeltaTimeMS ) { if( f_job_ ) f_job_( DeltaTimeMS ); }

private :
    JobContainer* p_container_ = nullptr;  /// 自信を保持しているコンテナ
    std::function<void(uint64_t)> f_job_;  /// セットされているタスク
};

///< Task : ジョブのセット
template <typename Object>
void Job::setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) )
{
    f_job_ = std::bind(
        pFunction,
        pOwner,
        std::placeholders::_1 );
}
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_HEADER_
/// EOF
