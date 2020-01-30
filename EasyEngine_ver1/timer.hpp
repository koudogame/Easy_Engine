///
/// @file   timer.hpp
///
#ifndef INCLUDED_EGEG_TIMER_HEADER_
#define INCLUDED_EGEG_TIMER_HEADER_
#include <cstdint>
#include <chrono>
#include "egeg_common.hpp"
BEGIN_EGEG
///
/// @class   Timer
///          
/// @brief   ���Ԍv���N���X
///          
/// @tparam  Unit : ���ԒP��
///
/// @details ���ԒP�ʂ̎w��ɂ́Astd::chrono���O��Ԃ̒P�ʂ��w�肵�Ă��������B<br>
///          ex.) auto erapsed = Timer.erapsed<std::chrono::milliseconds>();
///
template <typename Unit>
class Timer
{
public :
    ///
    /// @brief  ���Ԍv���J�n
    ///
    void start();
    ///
    /// @brief  ���Ԍv���X�g�b�v
    ///
    void stop();
    ///�@
    /// @brief  �v���ĊJ
    ///
    void resume();

    ///
    /// @brief  �o�ߎ��Ԏ擾
    ///
    /// @return �o�ߎ���
    ///
    uint64_t erapsed();
    
private :
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    uint64_t count_ = 0U;
};

///< �v���J�n
template <typename Unit>
void Timer<Unit>::start()
{
    count_ = 0U;
    start_ = std::chrono::high_resolution_clock::now();
}

///< �v���X�g�b�v
template <typename Unit>
void Timer<Unit>::stop()
{
    using namespace std::chrono;

    auto erapsed = high_resolution_clock::now() - start_;
    count_ += duration_cast<Unit>( erapsed ).Count();
}
END_EGEG
#endif /// !INCLUDED_EGEG_TIMER_HEADER_
/// EOF
