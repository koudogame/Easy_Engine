///
/// @file   name.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_NAME_HEADER_
#define INCLUDED_EGEG_NAME_HEADER_

#include <string>
#include "egeg_def.hpp"

BEGIN_EGEG

///
/// @struct  Name
/// @brief   文字列を返却するファンクタ
/// @details 注意 Name<"hoge">のように宣言できない。                  <br>
///          文字列を設定する際は、定数として定義した後その定数を渡します。 <br>
///          使用例 )                                                <br>
///           宣言                                                  <br>
///             static constexpr const char kHogeName = "hoge";     <br>
///             Name<kHogeName> name_generator{};
///
template <const char Name_[]>
struct Name
{
    std::string operator()() const noexcept
    {
        return std::string{ Name_ };
    }
};

END_EGEG
#endif /// !INCLUDED_EGEG_NAME_HEADER_
/// EOF
