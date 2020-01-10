///
/// @file   interface.hpp
/// @author 板場
///
/// @brief  インターフェイス基底クラス 
///         外部からの開放を制限しています。<br>
///         release関数で自身の開放処理を記述している。<br>
///         必要な開放処理は デストラクタに実装してください。
///
#ifndef INCLUDED_EG_EG_INTERFACE_HEADER_
#define INCLUDED_EG_EG_INTERFACE_HEADER_
#include "easy_engine.hpp"
BEGIN_EG_EG
class Interface
{
public :
    Interface() : ref_cnt_( 1U ) {}

    ///
    /// @brief  参照集を取得します。
    ///
    /// @return 参照数
    ///
    unsigned getReferencedNum() const { return ref_cnt_; }

    ///
    /// @brief  参照数インクリメント
    ///
    void addRef() { ++ref_cnt_; }
    ///
    /// @brief   開放処理
    /// @details 参照数をデクリメントし、参照者がいなくなったときに開放されます。
    ///
    void release()
    {
        if( --ref_cnt_ <= 0U )
        {
            delete this;
        }
    }

protected :
    virtual ~Interface() = default; ///< 外部からのデストラクタ呼び出しを制限しています。
private :
    unsigned ref_cnt_;  /// 参照数
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_INTERFACE_HEADER_
/// EOF
