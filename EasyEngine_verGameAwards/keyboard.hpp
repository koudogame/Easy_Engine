///
/// @file   keyboard.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_KEYBOARD_HEADER_
#define INCLUDED_EGEG_KEYBOARD_HEADER_
#include <cstdint>
#include <array>
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
        FlagType padding0[8];           // 0x00 ~ 0x07
        FlagType backspace;             // 0x08
        FlagType tab;                   // 0x09
        FlagType padding1[3];           // 0x0A ~ 0x0C
        FlagType enter;                 // 0x0D
        FlagType padding2[13];          // 0x0E ~ 0x1A
        FlagType escape;                // 0x1B
        FlagType padding3[4];           // 0x1C ~ 0x1F
        FlagType space;                 // 0x20
        FlagType padding4[4];           // 0x21 ~ 0x24
        FlagType left;                  // 0x25
        FlagType up;                    // 0x26
        FlagType right;                 // 0x27
        FlagType down;                  // 0x28
        FlagType padding5[7];           // 0x29 ~ 0x2F
        FlagType zero;                  // 0x30
        FlagType one;                   // 0x31
        FlagType two;                   // 0x32
        FlagType three;                 // 0x33
        FlagType four;                  // 0x34
        FlagType five;                  // 0x35
        FlagType six;                   // 0x36
        FlagType seven;                 // 0x37
        FlagType eight;                 // 0x38
        FlagType nine;                  // 0x39
        FlagType padding6[7];           // 0x3A ~ 0x40
        FlagType a;                     // 0x41
        FlagType b;                     // 0x42
        FlagType c;                     // 0x43
        FlagType d;                     // 0x44
        FlagType e;                     // 0x45
        FlagType f;                     // 0x46
        FlagType g;                     // 0x47
        FlagType h;                     // 0x48
        FlagType i;                     // 0x49
        FlagType j;                     // 0x4A
        FlagType k;                     // 0x4B
        FlagType l;                     // 0x4C
        FlagType m;                     // 0x4D
        FlagType n;                     // 0x4E
        FlagType o;                     // 0x4F
        FlagType p;                     // 0x50
        FlagType q;                     // 0x51
        FlagType r;                     // 0x52
        FlagType s;                     // 0x53
        FlagType t;                     // 0x54
        FlagType u;                     // 0x55
        FlagType v;                     // 0x56
        FlagType w;                     // 0x57
        FlagType x;                     // 0x58
        FlagType y;                     // 0x59
        FlagType z;                     // 0x5A
        FlagType left_windows;          // 0x5B
        FlagType right_windows;         // 0x5C
        FlagType padding7[3];           // 0x5D ~ 0x5F
        FlagType numpad_0;              // 0x60
        FlagType numpad_1;              // 0x61
        FlagType numpad_2;              // 0x62
        FlagType numpad_3;              // 0x63
        FlagType numpad_4;              // 0x64
        FlagType numpad_5;              // 0x65
        FlagType numpad_6;              // 0x66
        FlagType numpad_7;              // 0x67
        FlagType numpad_8;              // 0x68
        FlagType numpad_9;              // 0x69
        FlagType padding8[6];           // 0x6A ~ 0x6F
        FlagType f1;                    // 0x70
        FlagType f2;                    // 0x71
        FlagType f3;                    // 0x72
        FlagType f4;                    // 0x73
        FlagType f5;                    // 0x74
        FlagType f6;                    // 0x75
        FlagType f7;                    // 0x76
        FlagType f8;                    // 0x77
        FlagType f9;                    // 0x78
        FlagType f10;                   // 0x79
        FlagType f11;                   // 0x7A
        FlagType f12;                   // 0x7B
        FlagType padding9[36];          // 0x7C ~ 0x9F
        FlagType left_shift;            // 0xA0
        FlagType right_shift;           // 0xA1
        FlagType left_ctrl;             // 0xA2
        FlagType right_ctrl;            // 0xA3
        FlagType left_alt;              // 0xA4
        FlagType right_alt;             // 0xA5
        FlagType padding10[20];         // 0xA6 ~ 0xB9
        FlagType colon;                 // 0xBA
        FlagType semicolon;             // 0xBB
        FlagType comma;                 // 0xBC
        FlagType minus;                 // 0xBD
        FlagType period;                // 0xBE
        FlagType slash;                 // 0xBF
        FlagType atmark;                // 0xC0
        FlagType padding11[26];         // 0xC1 ~ 0xDA
        FlagType left_square_bracket;   // 0xDB
        FlagType backslash;             // 0xDC
        FlagType right_square_bracket;  // 0xDD
        FlagType caret;                 // 0xDE
        FlagType padding12[17];         // 0xDF ~ 0xEF
        FlagType caps_lock;             // 0xF0
        FlagType padding13[2];          // 0xF1 ~ 0xF2
        FlagType kanji;                 // 0xF3
        FlagType padding14[11];         // 0xF4 ~ 0xFE
    };

    ///< インスタンスの取得
    static Keyboard* instance() noexcept { static Keyboard i; return &i; }

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
    Keyboard() noexcept;

    void keyDown( uint8_t ) noexcept;
    void keyUp( uint8_t ) noexcept;
    FlagType newState( uint8_t ) noexcept;

    State state_ = {};

    std::array<uint8_t, 32U> raw_;  /// 256bit
    std::array<uint8_t, 32U> last_; /// 256bit
};
END_EGEG
#endif /// !INCLUDED_EGEG_KEYBOARD_HEADER_
/// EOF
