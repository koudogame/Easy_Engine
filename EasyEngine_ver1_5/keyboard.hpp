///
/// @file   keyboard.hpp
/// @author 板場
/// 
#ifndef INCLUDED_EGEG_KEYBOARD_HEADER_
#define INCLUDED_EGEG_KEYBOARD_HEADER_

#include <array>
#include <Windows.h>
#include "input_device.hpp"

BEGIN_EGEG

///
/// @class Keyboard
/// @brief キーボード
///
class Keyboard :
    public InputDevice
{
public :
    struct State
    {
        InputType padding0[8];           // 0x00 ~ 0x07
        InputType backspace;             // 0x08
        InputType tab;                   // 0x09
        InputType padding1[3];           // 0x0A ~ 0x0C
        InputType enter;                 // 0x0D
        InputType padding2[13];          // 0x0E ~ 0x1A
        InputType escape;                // 0x1B
        InputType padding3[4];           // 0x1C ~ 0x1F
        InputType space;                 // 0x20
        InputType padding4[4];           // 0x21 ~ 0x24
        InputType left;                  // 0x25
        InputType up;                    // 0x26
        InputType right;                 // 0x27
        InputType down;                  // 0x28
        InputType padding5[7];           // 0x29 ~ 0x2F
        InputType zero;                  // 0x30
        InputType one;                   // 0x31
        InputType two;                   // 0x32
        InputType three;                 // 0x33
        InputType four;                  // 0x34
        InputType five;                  // 0x35
        InputType six;                   // 0x36
        InputType seven;                 // 0x37
        InputType eight;                 // 0x38
        InputType nine;                  // 0x39
        InputType padding6[7];           // 0x3A ~ 0x40
        InputType a;                     // 0x41
        InputType b;                     // 0x42
        InputType c;                     // 0x43
        InputType d;                     // 0x44
        InputType e;                     // 0x45
        InputType f;                     // 0x46
        InputType g;                     // 0x47
        InputType h;                     // 0x48
        InputType i;                     // 0x49
        InputType j;                     // 0x4A
        InputType k;                     // 0x4B
        InputType l;                     // 0x4C
        InputType m;                     // 0x4D
        InputType n;                     // 0x4E
        InputType o;                     // 0x4F
        InputType p;                     // 0x50
        InputType q;                     // 0x51
        InputType r;                     // 0x52
        InputType s;                     // 0x53
        InputType t;                     // 0x54
        InputType u;                     // 0x55
        InputType v;                     // 0x56
        InputType w;                     // 0x57
        InputType x;                     // 0x58
        InputType y;                     // 0x59
        InputType z;                     // 0x5A
        InputType left_windows;          // 0x5B
        InputType right_windows;         // 0x5C
        InputType padding7[3];           // 0x5D ~ 0x5F
        InputType numpad_0;              // 0x60
        InputType numpad_1;              // 0x61
        InputType numpad_2;              // 0x62
        InputType numpad_3;              // 0x63
        InputType numpad_4;              // 0x64
        InputType numpad_5;              // 0x65
        InputType numpad_6;              // 0x66
        InputType numpad_7;              // 0x67
        InputType numpad_8;              // 0x68
        InputType numpad_9;              // 0x69
        InputType padding8[6];           // 0x6A ~ 0x6F
        InputType f1;                    // 0x70
        InputType f2;                    // 0x71
        InputType f3;                    // 0x72
        InputType f4;                    // 0x73
        InputType f5;                    // 0x74
        InputType f6;                    // 0x75
        InputType f7;                    // 0x76
        InputType f8;                    // 0x77
        InputType f9;                    // 0x78
        InputType f10;                   // 0x79
        InputType f11;                   // 0x7A
        InputType f12;                   // 0x7B
        InputType padding9[36];          // 0x7C ~ 0x9F
        InputType left_shift;            // 0xA0
        InputType right_shift;           // 0xA1
        InputType left_ctrl;             // 0xA2
        InputType right_ctrl;            // 0xA3
        InputType left_alt;              // 0xA4
        InputType right_alt;             // 0xA5
        InputType padding10[20];         // 0xA6 ~ 0xB9
        InputType colon;                 // 0xBA
        InputType semicolon;             // 0xBB
        InputType comma;                 // 0xBC
        InputType minus;                 // 0xBD
        InputType period;                // 0xBE
        InputType slash;                 // 0xBF
        InputType atmark;                // 0xC0
        InputType padding11[26];         // 0xC1 ~ 0xDA
        InputType left_square_bracket;   // 0xDB
        InputType backslash;             // 0xDC
        InputType right_square_bracket;  // 0xDD
        InputType caret;                 // 0xDE
        InputType padding12[17];         // 0xDF ~ 0xEF
        InputType caps_lock;             // 0xF0
        InputType padding13[2];          // 0xF1 ~ 0xF2
        InputType kanji;                 // 0xF3
        InputType padding14[11];         // 0xF4 ~ 0xFE
    };

    Keyboard() noexcept;

    ///
    /// @brief イベント処理
    ///
    /// @param[in] Message : イベントメッセージ
    /// @param[in] wParam  : パラメータ
    /// @param[in] lParam  : パラメータ
    ///
    void eventProcessing( UINT Message, WPARAM wParam, LPARAM lParam ) noexcept;

    ///
    /// @brief 入力状態の取得
    ///
    const State& getState() const noexcept { return state_; }

// override
    void update() override;

private :
    void keyDown( uint8_t ) noexcept;
    void keyUp( uint8_t ) noexcept;

    State state_{};
    std::array<uint8_t, 32U> raw_;  ///< 256bit
    std::array<uint8_t, 32U> last_; ///< 256bit
};

END_EGEG
#endif /// !INCLUDED_EGEG_KEYBOARD_HEADER_
/// EOF
