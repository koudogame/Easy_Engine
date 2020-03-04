///
/// @file   job.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_HEADER_
#define INCLUDED_EGEG_JOB_HEADER_
#include <functional>
#include "job_container.hpp"
BEGIN_EGEG
///
/// @class   Job
/// @brief   ジョブ
///
/// @tparam RetValType : ジョブとして実行する関数の、戻り値型
/// @tparam ...Args    : ジョブとして実行する関数の、仮引数型( パラメータパック )
///
template <class RetValType, class ...Args>
class Job
{
public :
    using Signature = RetValType(Args...);
    using FunctionType = std::function<Signature>;

    ~Job() { exitFromContainer(); } 

    ///
    /// @brief  ジョブのセット
    ///
    /// @param[in] Function : ジョブとして登録する関数オブジェクト
    ///
    void setJob( FunctionType Function )
    {
        job_ = std::move( Function );
    }

    ///
    /// @brief   所属するコンテナの設定
    /// @details 既にコンテナに所属している場合、現在のコンテナから抜けた後にコンテナを設定します。
    ///
    /// @param[in] Container : 所属するコンテナ
    ///
    void setContainer( JobContainer<Job<Signature>>* Container ) { exitFromContainer(); container_ = Container; }
    ///< 所属するコンテナの取得
    JobContainer<Job<Signature>>* getContainer() const noexcept { return container_; }

    ///
    /// @brief   所持しているジョブの実行
    /// @details ジョブを所持していない場合、何も行いません。
    ///
    /// @param[in] Param : ジョブとして登録されている関数へ転送する引数リスト
    ///
    void operator()( Args ...Param ) { if( job_ ) job_( Param... ); }

    ///
    /// @brief   現在所属しているコンテナから抜ける
    /// @details コンテナに所属していない場合、何も処理を行いません。
    ///
    void exitFromContainer()
    {
        if( container_ )
        {
            container_->exit( this );
            container_ = nullptr;
        }
    }

private :
    FunctionType job_;
    JobContainer<Job<Signature>>* container_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_HEADER_
/// EOF
