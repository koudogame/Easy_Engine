///
/// @file    component.hpp
/// @author  板場
///          
/// @brief   コンポーネント
/// @details 各派生クラスは static uint16_t getComponentID() を実装してください。<br>
///          GETCOMPONENTIDマクロを使用すると楽です。
///
#ifndef INCLUDED_EGEG_COMPONENT_HEADER_
#define INCLUDED_EGEG_COMPONENT_HEADER_
#include <cstdint>
#include "egeg_common.hpp"
///
/// @def    GETCOMPONENTID
/// @brief  IDの取得関数をinlineで定義します。
///
/// @param[in] ID : 設定するID
///
#define GETCOMPONENTID( ID ) inline static uint16_t getComponentID() { return ID; }

BEGIN_EGEG
class IComponent
{
public :
    virtual ~IComponent() = default;

    ///
    /// @brief  初期化
    ///
    /// @return 初期化成功[ true ] 初期化失敗[ false ]
    ///
    virtual bool initialize() = 0;
    ///
    /// @brief  終了
    ///
    virtual void finalize() = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_COMPONENT_HEADER_
/// EOF
