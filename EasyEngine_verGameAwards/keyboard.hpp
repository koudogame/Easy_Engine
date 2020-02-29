///
/// @file   keyboard.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_KEYBOARD_HEADER_
#define INCLUDED_EGEG_KEYBOARD_HEADER_
#include <cstdint>
#include <Windows.h>
#include "input_device.hpp"
BEGIN_EGEG
///
/// @class  Keyboard
/// @brief  キーボードからの入力を取得する
///
class Keyboard :
    public InputDevice
{
public :
    ///< 入力状態格納構造体
    struct State
    {
        FlagType backspace;
        FlagType tab;
        FlagType enter;
        FlagType escape;
        FlagType space;
        FlagType left;
        FlagType up;
        FlagType right;
        FlagType down;
        FlagType zero;
        FlagType one;
        FlagType two;
        FlagType three;
        FlagType four;
        FlagType five;
        FlagType six;
        FlagType seven;
        FlagType eight;
        FlagType nine;
        FlagType a;
        FlagType b;
        FlagType c;
        FlagType d;
        FlagType e;
        FlagType f;
        FlagType g;
        FlagType h;
        FlagType i;
        FlagType j;
        FlagType k;
        FlagType l;
        FlagType m;
        FlagType n;
        FlagType o;
        FlagType p;
        FlagType q;
        FlagType r;
        FlagType s;
        FlagType t;
        FlagType u;
        FlagType v;
        FlagType w;
        FlagType x;
        FlagType y;
        FlagType z;
        FlagType left_windows;
        FlagType right_windows;
        FlagType numpad_0;
        FlagType numpad_1;
        FlagType numpad_2;
        FlagType numpad_3;
        FlagType numpad_4;
        FlagType numpad_5;
        FlagType numpad_6;
        FlagType numpad_7;
        FlagType numpad_8;
        FlagType numpad_9;
        FlagType f1;
        FlagType f2;
        FlagType f3;
        FlagType f4;
        FlagType f5;
        FlagType f6;
        FlagType f7;
        FlagType f8;
        FlagType f9;
        FlagType f10;
        FlagType f11;
        FlagType f12;
        FlagType left_shift;
        FlagType right_shift;
        FlagType left_ctrl;
        FlagType right_ctrl;
        FlagType left_alt;
        FlagType right_alt;
        FlagType colon;
        FlagType semicolon;
        FlagType comma;
        FlagType minus;
        FlagType period;
        FlagType slash;
        FlagType atmark;
        FlagType left_square_bracket;
        FlagType right_square_bracket;
        FlagType yen;
        FlagType caret;
        FlagType backslash;
        FlagType caps_lock;
        FlagType kanji;
    };

    Keyboard() noexcept;

    ///
    /// @brief  イベント処理
    ///
    /// @param[in] Message : イベントめせーじ
    /// @param[in] wParam  : 仮想キーコードを格納したパラメータ
    /// @param[in] lParam  : キーデータを格納したパラメータ
    ///
    void eventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) noexcept;
        
    ///< 入力状態取得
    const State& getState() const noexcept { return state_; }

/*-----------------------------------------------------------------*/
// InputDevice
    ///< 更新処理
    void update() override;
/*-----------------------------------------------------------------*/

private :
    void keyDown( uint8_t ) noexcept;
    void keyUp( uint8_t ) noexcept;
    FlagType newState( uint8_t ) noexcept;

    State state_ = {};
    uint8_t state_0_[32] = { 0 }; /// 256 bit
    uint8_t state_1_[32] = { 0 }; /// 256 bit
    uint8_t* curr_state_;
    uint8_t* last_state_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_KEYBOARD_HEADER_
/// EOF
