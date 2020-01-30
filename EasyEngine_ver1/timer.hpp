///
/// @file   timer.hpp
/// @author 板場
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
/// @brief   時間計測クラス
///          
/// @tparam  Unit : 時間単位
///
/// @details 時間単位の指定には、std::chrono名前空間の単位を指定してください。<br>
///          ex.) auto erapsed = Timer.erapsed<std::chrono::milliseconds>();
///
template <typename Unit>
class Timer
{
public :
    ///
    /// @brief  時間計測開始
    ///
    void start();
    ///
    /// @brief  時間計測ストップ
    ///
    void stop();
    ///　
    /// @brief  計測再開
    ///
    void resume();

    ///
    /// @brief  経過時間取得
    ///
    /// @return 経過時間
    ///
    uint64_t erapsed();
    
private :
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    bool is_stop_   = false;
    uint64_t count_ = 0U;
};

///< 計測開始
template <typename Unit>
void Timer<Unit>::start()
{
    is_stop_ = false;
    count_ = 0U;
    start_ = std::chrono::high_resolution_clock::now();
}

///< 計測ストップ
template <typename Unit>
void Timer<Unit>::stop()
{
    using namespace std::chrono;

    // 既に止まっている
    if( is_stop_ ) return;

    is_stop_ = true;
    auto erapsed = high_resolution_clock::now() - start_;
    count_ += duration_cast<Unit>( erapsed ).Count();
}

///< 計測再開
template <typename Unit>
void Timer<Unit>::resume()
{
    // 既に動いている
    if( is_stop_ == false ) return;

    is_stop_ = false;
    start_ = std::chrono::high_resolution_clock::now();
}

///< 経過時間取得
template <typename Unit>
uint64_t Timer<Unit>::erapsed()
{
    using namespace std::chrono;

    if( is_stop_ )
    {
        return count_;
    }
    else
    {
        auto erapsed = high_resolution_clock::now() - start_;
        return count_ + duration_cast<Unit>(erapsed).Count();
    }
}
END_EGEG
#endif /// !INCLUDED_EGEG_TIMER_HEADER_
/// EOF
