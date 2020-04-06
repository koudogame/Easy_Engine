///
/// @file   job.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_HEADER_
#define INCLUDED_EGEG_JOB_HEADER_

#include <functional>
#include "noncopyable.hpp"
#include "job_container.hpp"

BEGIN_EGEG

///
/// @class   Job
/// @brief   �W���u
///
/// @tparam FunctionType : �W���u�̊֐��^ ex.) float(int, int)
///
template <class FunctionType>
class Job;

///< Job��`
template <class RetValType, class ...ArgTypes>
class Job<RetValType(ArgTypes...)> : NonCopyable<Job<RetValType(ArgTypes...)>>
{
public :
    using ReturnValueType = RetValType;

    ///< �f�X�g���N�^
    ~Job() { exitFromContainer(); } 

    ///
    /// @brief  �W���u�̃Z�b�g
    ///
    /// @param[in] Function : �W���u�Ƃ��ēo�^����֐��I�u�W�F�N�g
    ///
    template <class FunctionType>
    void setJob( FunctionType&& Function )
    {
        job_ = std::forward<FunctionType>( Function );
    }

    ///
    /// @brief   ��������R���e�i�̐ݒ�
    /// @details ���ɃR���e�i�ɏ������Ă���ꍇ�A���݂̃R���e�i���甲������ɃR���e�i��ݒ肵�܂��B
    ///
    /// @param[in] Container : ��������R���e�i
    ///
    void setContainer( JobContainer<Job>* Container ) { exitFromContainer(); container_ = Container; }
    ///< ��������R���e�i�̎擾
    JobContainer<Job>* getContainer() const noexcept { return container_; }

    ///
    /// @brief   �������Ă���W���u�̎��s
    /// @details �W���u���������Ă��Ȃ��ꍇ��bad_function_call��O�𑗏o���܂��B<br>
    ///          ���߂�l��ԋp���邽�߂ɁA���s���Ȃ��Ƃ����I���������Ȃ����߂ł��B
    ///
    /// @param[in] Param : �W���u�Ƃ��ēo�^����Ă���֐��֓]������������X�g
    ///
    RetValType operator()( ArgTypes ...Args ) { return job_( Args... ); }

    ///
    /// @brief   ���ݏ������Ă���R���e�i���甲����
    /// @details �R���e�i�ɏ������Ă��Ȃ��ꍇ�A�����������s���܂���B
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
    JobContainer<Job>* container_ = nullptr;
};

END_EGEG
#endif /// !INCLUDED_EGEG_JOB_HEADER_
/// EOF
