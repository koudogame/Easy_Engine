///
/// @file   interface.hpp
/// @author 板場
///
/// @brief  インターフェイス基底クラス 
///         外部からの開放を制限しています。<br>
///         release関数で自身の開放処理を記述してください。
///
#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Interface
{
public :
    ///
    /// @brief  参照数インクリメント
    ///
    virtual void addRef() = 0;
    ///
    /// @brief   開放処理
    /// @details 参照数をデクリメントし、参照者がいなくなったときに開放されます。
    ///
    virtual void release() = 0;

protected :
    virtual ~Interface() = default; ///< 外部からのデストラクタ呼び出しを制限しています。
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_INTERFACE_HEADER_
/// EOF
