///
/// @file    job.hpp
/// @author  ��
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
/// @brief   �W���u�ŏ��P��
/// @details JobScheduler�ɓo�^�����ŏ��P�ʂł��B<br>
///          JobContainer�ɂ��ێ�����܂��B
///
class Job
{
public :
    ///
    /// @brief  �W���u�Ƃ��Ď��s����֐��̃Z�b�g
    ///
    /// @tparam Object : �W���u�̕ێ��҂̌^( �ȗ��� )
    ///
    /// @param[in] pOwner : �W���u�̕ێ���
    /// @param[in] pFunction : �Z�b�g����֐��̃A�h���X
    ///
    template <typename Object>
    void setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) );

    ///
    /// @brief  �R���e�i�̃Z�b�g
    ///
    /// @param[in] pContainer : ���M��ێ�����R���e�i
    ///
    void setContainer( JobContainer* pContainer ) { p_container_ = pContainer; }
    ///
    /// @brief  �R���e�i�̎擾
    ///
    /// @return ���M��ێ����Ă���R���e�i
    ///
    JobContainer* getContainer() const { return p_container_; }

    ///
    /// @brief  �Z�b�g����Ă���W���u�̎��s
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎��Ԃ̍�(: �~���b)
    ///
    void operator()( uint64_t DeltaTimeMS ) { if( f_job_ ) f_job_( DeltaTimeMS ); }

private :
    JobContainer* p_container_ = nullptr;  /// ���M��ێ����Ă���R���e�i
    std::function<void(uint64_t)> f_job_;  /// �Z�b�g����Ă���^�X�N
};

///< Task : �W���u�̃Z�b�g
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
