///
/// @file    task.hpp
/// @author  ��
///          
/// @brief   �^�X�N�P��
/// @details TaskManager�ɓo�^�����ŏ��P�ʂł��B<br>
///          TaskContainer�ɂ��ێ�����܂��B
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
    /// @brief  �^�X�N�Ƃ��Ď��s����֐��̃Z�b�g
    ///
    /// @tparam Object : �^�X�N�̕ێ��҂̌^( �ȗ��� )
    ///
    /// @param[in] pOwner : �^�X�N�̕ێ���
    /// @param[in] pFunction : �Z�b�g����֐��̃A�h���X
    ///
    template <typename Object>
    void setFunction( Object* pOwner, void(Object::*pFunction)(uint64_t) );

    ///
    /// @brief  �R���e�i�̃Z�b�g
    ///
    /// @param[in] pContainer : ���M��ێ�����R���e�i
    ///
    void setContainer( TaskContainer* pContainer ) { p_container_ = pContainer; }
    ///
    /// @brief  �R���e�i�̎擾
    ///
    /// @return ���M��ێ����Ă���R���e�i
    ///
    TaskContainer* getContainer() const { return p_container_; }

    ///
    /// @brief  �Z�b�g����Ă���^�X�N�̎��s
    ///
    /// @param[in] DeltaTimeMS : �O��Ăяo��������̎��Ԃ̍�(: �~���b)
    ///
    void operator()( uint64_t DeltaTimeMS ) { if( f_task_ ) f_task_( DeltaTimeMS ); }

private :
    TaskContainer* p_container_ = nullptr;  /// ���M��ێ����Ă���R���e�i
    std::function<void(uint64_t)> f_task_;  /// �Z�b�g����Ă���^�X�N
};

///< Task : �^�X�N�̃Z�b�g
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
