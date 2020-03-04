///
/// @file   job.hpp
/// @author ��
///
#ifndef INCLUDED_EGEG_JOB_HEADER_
#define INCLUDED_EGEG_JOB_HEADER_
#include <functional>
#include "job_container.hpp"
BEGIN_EGEG
///
/// @class   Job
/// @brief   �W���u
///
/// @tparam RetValType : �W���u�Ƃ��Ď��s����֐��́A�߂�l�^
/// @tparam ...Args    : �W���u�Ƃ��Ď��s����֐��́A�������^( �p�����[�^�p�b�N )
///
template <class RetValType, class ...Args>
class Job
{
public :
    using Signature = RetValType(Args...);
    using FunctionType = std::function<Signature>;

    ~Job() { exitFromContainer(); } 

    ///
    /// @brief  �W���u�̃Z�b�g
    ///
    /// @param[in] Function : �W���u�Ƃ��ēo�^����֐��I�u�W�F�N�g
    ///
    void setJob( FunctionType Function )
    {
        job_ = std::move( Function );
    }

    ///
    /// @brief   ��������R���e�i�̐ݒ�
    /// @details ���ɃR���e�i�ɏ������Ă���ꍇ�A���݂̃R���e�i���甲������ɃR���e�i��ݒ肵�܂��B
    ///
    /// @param[in] Container : ��������R���e�i
    ///
    void setContainer( JobContainer<Job<Signature>>* Container ) { exitFromContainer(); container_ = Container; }
    ///< ��������R���e�i�̎擾
    JobContainer<Job<Signature>>* getContainer() const noexcept { return container_; }

    ///
    /// @brief   �������Ă���W���u�̎��s
    /// @details �W���u���������Ă��Ȃ��ꍇ�A�����s���܂���B
    ///
    /// @param[in] Param : �W���u�Ƃ��ēo�^����Ă���֐��֓]������������X�g
    ///
    void operator()( Args ...Param ) { if( job_ ) job_( Param... ); }

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
    FunctionType job_;
    JobContainer<Job<Signature>>* container_ = nullptr;
};
END_EGEG
#endif /// !INCLUDED_EGEG_JOB_HEADER_
/// EOF
