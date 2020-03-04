///
/// @file   job.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_JOB_HEADER_
#define INCLUDED_EGEG_JOB_HEADER_
#include <functional>
#include "egeg_utility.hpp"
#include "job_container.hpp"
BEGIN_EGEG
///
/// @class   Job
/// @brief   ジョブ
///
/// @tparam FunctionType : ジョブの関数型 ex.) float(int, int)
///
template <class FunctionType>
class Job;

///< Job定義
template <class RetValType, class ...ArgTypes>
class Job<RetValType(ArgTypes...)> : NonCopyable<Job<RetValType(ArgTypes...)>>
{
public :
    using ReturnValueType = RetValType;

    ///< デストラクタ
    ~Job() { exitFromContainer(); } 

    ///
    /// @brief  ジョブのセット
    ///
    /// @param[in] Function : ジョブとして登録する関数オブジェクト
    ///
    void setJob( std::function<RetValType(ArgTypes...)> Function )
    {
        job_ = std::move( Function );
    }

    ///
    /// @brief   所属するコンテナの設定
    /// @details 既にコンテナに所属している場合、現在のコンテナから抜けた後にコンテナを設定します。
    ///
    /// @param[in] Container : 所属するコンテナ
    ///
    void setContainer( JobContainer<Job<RetValType(ArgTypes...)>>* Container ) { exitFromContainer(); container_ = Container; }
    ///< 所属するコンテナの取得
    JobContainer<Job<RetValType(ArgTypes...)>>* getContainer() const noexcept { return container_; }

    ///
    /// @brief   所持しているジョブの実行
    /// @details ジョブを所持していない場合はbad_function_call例外を送出します。<br>
    ///          ↑戻り値を返却するために、実行しないという選択肢が取れない。
    ///
    /// @param[in] Param : ジョブとして登録されている関数へ転送する引数リスト
    ///
    RetValType operator()( ArgTypes ...Args ) { return job_( Args... ); }

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
    std::function<RetValType(ArgTypes...)> job_;
    JobContainer<Job<RetValType(ArgTypes...)>>* container_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_HEADER_
/// EOF
